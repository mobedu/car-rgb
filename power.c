#include "power.h"

// Battery brightness curve lookup table
// ADC value -> max brightness (0-255)
// Voltage range: 3.5V-4.2V
static const unsigned char battery_brightness_curve[] = {
    255,    // 4.20V (ADC ~1785)
    200,    // 4.15V (ADC ~1770)
    186,    // 4.10V (ADC ~1750)
    178,    // 4.05V (ADC ~1730)
    170,    // 4.00V (ADC ~1710)
    162,    // 3.95V (ADC ~1690)
    154,    // 3.90V (ADC ~1669)
    146,    // 3.85V (ADC ~1649)
    138,    // 3.80V (ADC ~1626)
    90      // 3.50V (ADC ~1493) - 低电压保护
};

// Solar control state
// solar_auto_enabled = 1: 环境暗，可以开灯; 0: 环境亮，关灯
unsigned char solar_auto_enabled = 1;
static unsigned int solar_check_counter = 0;

// ========== ADC Initialize ==========
void adc_init(void) {
    // Enable ADC module
    ADON = 1;

    // VREF: VDD/VSS, Left justify, Clock = FOSC/32
    ADCON1 = 0x30;
    ADCON2 = 0x94;

    // Set ADC input pins as analog (RA2=AN2, RA3=AN3)
    ANSEL0 = 0x0C;   // RA2, RA3 as analog
    ANSEL1 = 0;
}

// ========== Read Battery ADC (AN2: RA2) ==========
unsigned int battery_read_adc(void) {
    unsigned int adval;

    // Select channel AN2 (RA2): CHS = 2
    ADCON0 = 0x08;    // ADON=1, CHS=2

    // Wait acquisition time (~15us)
    for (adval = 0; adval < 50; adval++) asm("nop");

    GO = 1;         // Start conversion
    while (GO);      // Wait complete

    adval = (unsigned int)((ADRESH << 8) | ADRESL);
    return adval;
}

// ========== Read Solar ADC (AN3: RA3) ==========
unsigned int solar_read_adc(void) {
    unsigned int adval;

    // Select channel AN3 (RA3): CHS = 3
    ADCON0 = 0x0C;    // ADON=1, CHS=3

    // Wait acquisition time (~15us)
    for (adval = 0; adval < 50; adval++) asm("nop");

    GO = 1;         // Start conversion
    while (GO);      // Wait complete

    adval = (unsigned int)((ADRESH << 8) | ADRESL);
    return adval;
}

// ========== Get Battery Brightness ==========
unsigned char get_battery_brightness(unsigned int bat_adc) {
    unsigned int idx;

    // Index: ADC 1493-1785 (3.5V-4.2V) -> 0-9 (range 292)
    // 3.5V = 1493, 4.2V = 1785, step = 292/9 ≈ 32
    if (bat_adc < 1493) return BAT_MIN_BRIGHTNESS;
    if (bat_adc >= 1785) return BAT_MAX_BRIGHTNESS;

    idx = (bat_adc - 1493) / 33;
    if (idx >= 10) idx = 9;

    return battery_brightness_curve[idx];
}

// ========== Solar Auto Control ==========
void solar_auto_control(void) {
    unsigned int solar_adc;

    // Check every ~500ms to avoid jitter
    if (++solar_check_counter < 500) return;
    solar_check_counter = 0;

    solar_adc = solar_read_adc();

    // Threshold logic (with hysteresis):
    // Strong light (>2.3V) -> ADC > 1000 -> turn OFF
    // Weak light (<0.9V) -> ADC < 800 -> turn ON
    if (solar_adc > 1000) {
        solar_auto_enabled = 0;   // Too bright, disable lights
    } else if (solar_adc < 800) {
        solar_auto_enabled = 1;   // Dark enough, enable lights
    }
}

// ========== Power Off LEDs ==========
void power_off_leds(RGB_t *leds) {
    unsigned char i;
    for (i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}