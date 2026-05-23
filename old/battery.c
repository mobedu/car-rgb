#include <sc.h>
#include "battery.h"
#include "config.h"

unsigned char battery_brightness_limit = 255;
unsigned char battery_current_limit = 255;
unsigned char battery_fade_counter = 0;
unsigned char battery_protected = 0;

void battery_adc_init(void) {
    // 配置 AN8 (RB0) 用于电池检测
    ANSEL1 |= (1 << 0);
    TRISB |= (1 << 0);
    ADCON0 = (ADCON0 & 0xC0) | (8 << 2);
    ADCON0 |= 0x01;
}

unsigned int battery_read_voltage(void) {
    unsigned int adc;
    // 设置 AN8
    ADCON0 = (ADCON0 & 0xC3) | (8 << 2);
    ADCON0 |= 0x02;
    while (ADCON0 & 0x02) asm("clrwdt");
    adc = (ADRESH << 8) | ADRESL;
    // 电压 = (ADC/1023) * 2.4V / 分压比
    unsigned long v = ((unsigned long)adc * ADC_REF_MV * 10000) / (ADC_RESOLUTION * BAT_DIVIDER);
    return (unsigned int)(v / 10);
}

BatteryStatus_t battery_get_status(void) {
    unsigned int v = battery_read_voltage();
    if (v >= BAT_MAX_MV) return BATTERY_FULL;
    if (v >= 3800) return BATTERY_HIGH;
    if (v >= 3500) return BATTERY_MEDIUM;
    if (v >= BAT_PROTECT_MV) return BATTERY_LOW;
    return BATTERY_PROTECTED;
}

void battery_update_brightness_limit(void) {
    BatteryStatus_t s = battery_get_status();
    unsigned char tbl[5] = {255, 220, 180, 140, 100};
    battery_brightness_limit = tbl[s];
}

void battery_fade_update(void) {
    if (battery_current_limit == battery_brightness_limit) return;
    if (++battery_fade_counter >= 250) {
        battery_fade_counter = 0;
        signed char d = (signed char)battery_brightness_limit - (signed char)battery_current_limit;
        if (d > 0) battery_current_limit++;
        else if (d < 0) battery_current_limit--;
    }
}

unsigned char battery_check_protection(void) {
    unsigned int v = battery_read_voltage();
    if (v < BAT_PROTECT_MV && !battery_protected) {
        battery_protected = 1;
        return 1;
    }
    if (v > BAT_RECOVER_MV && battery_protected) {
        battery_protected = 0;
        return 0;
    }
    return battery_protected;
}

void battery_clear_protect(void) {
    battery_protected = 0;
}