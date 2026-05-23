#include <sc.h>
#include "config.h"
#include "effects_new.h"
#include "ws2812.h"
#include "battery.h"
#include "rf433.h"
#include "vibration.h"
#include "power.h"
#include "cds.h"
#include "iservices.h"

unsigned char power_state = 1;

void system_clock_init(void) {
    OSCCON = 0x70;
}

void delay_ms(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms; i++) {
        unsigned int j = 1333;
        while (j--) asm("nop");
    }
}

// 使用volatile写代替asm("nop")，防止编译器将延迟指令重排到SFR操作之后
volatile unsigned char __ws_dly;

void ws2812_send_byte(unsigned char b) {
    // 1码: 延迟在高电平阶段, 0码: 延迟在低电平阶段

    // Bit 7
    if (b & 0x80) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
    // Bit 6
    if (b & 0x40) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
    // Bit 5
    if (b & 0x20) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
    // Bit 4
    if (b & 0x10) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
    // Bit 3
    if (b & 0x08) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
    // Bit 2
    if (b & 0x04) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
    // Bit 1
    if (b & 0x02) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
    // Bit 0
    if (b & 0x01) {
        RB1 = 1; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; RB1 = 0;
    } else {
        RB1 = 1; RB1 = 0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0; __ws_dly=0;
    }
}

void ws2812_send_color(RGB_t c) {
    ws2812_send_byte(c.g);
    ws2812_send_byte(c.r);
    ws2812_send_byte(c.b);
}

void ws2812_update_RGB(RGB_t *l, unsigned char n) {
    unsigned char i;
    GIE = 0;
    for (i = 0; i < n; i++) ws2812_send_color(l[i]);
    RB1 = 0;
    delay_ms(1);
    GIE = 1;
}

static void gpio_init(void) {
    // RA0: 按键
    TRISA |= (1 << 0);
    ANSEL0 &= ~(1 << 0);
    WPUA |= (1 << 0);

    // RA1: 震动
    TRISA |= (1 << 1);
    ANSEL0 &= ~(1 << 1);

    // RA2: RF433 SHUT
    TRISA &= ~(1 << 2);
    ANSEL0 &= ~(1 << 2);

    // RB0: 电池 ADC
    TRISB |= (1 << 0);

    // RB1: WS2812B
    TRISB &= ~(1 << 1);
    ANSEL1 &= ~(1 << 1);
    RB1 = 0;

    // RB2: 光敏 ADC
    TRISB |= (1 << 2);
}

static unsigned char key_counter = 0;
static unsigned char key_pressed = 0;

void key_scan(void) {
    if (RA0 == 0) {
        if (!key_pressed) {
            delay_ms(20);
            if (RA0 == 0) {
                key_pressed = 1;
                key_counter = 0;
            }
        } else if (++key_counter == 200) {
            power_state = !power_state;
            if (!power_state) {
                unsigned char i;
                for (i = 0; i < LED_COUNT; i++) leds[i].r = leds[i].g = leds[i].b = 0;
                ws2812_update_RGB(leds, LED_COUNT);
            } else {
                if (!battery_check_protection()) {
                    battery_clear_protect();
                    effect_new_execute(current_effect);
                }
            }
            while (RA0 == 0) asm("clrwdt");
            key_pressed = key_counter = 0;
        }
    } else if (key_pressed) {
        if (key_counter < 200 && power_state) {
            if (battery_check_protection()) {
                key_pressed = key_counter = 0;
                return;
            }
            if (current_effect <= EFFECT_FAST_FLASH) {
                g_color_index = (g_color_index + 1) % 10;
                effect_new_execute(current_effect);
            } else {
                effect_new_execute((current_effect + 1) % 7);
            }
        }
        key_pressed = key_counter = 0;
        power_reset_idle_counter();
    }
}

static unsigned char dim_level = 0;

static unsigned char apply_limits(unsigned char v) {
    static const unsigned char dim_tbl[4] = {255, 192, 128, 64};
    unsigned long t = (unsigned long)v * battery_current_limit * dim_tbl[dim_level];
    return (unsigned char)(t >> 16);
}

void rf433_process_command(void) {
    unsigned char cmd = rf433_get_command();
    unsigned char i;

    switch (cmd) {
        case RF433_CMD_OFF:
            power_state = 0;
            for (i = 0; i < LED_COUNT; i++) leds[i].r = leds[i].g = leds[i].b = 0;
            ws2812_update_RGB(leds, LED_COUNT);
            break;
        case RF433_CMD_ON:
            if (!battery_check_protection()) {
                power_state = 1;
                battery_clear_protect();
                effect_new_execute(current_effect);
            }
            break;
        case RF433_CMD_TIME_4H: timer_state = TIMER_4H; timer_counter = 0; break;
        case RF433_CMD_TIME_6H: timer_state = TIMER_6H; timer_counter = 0; break;
        case RF433_CMD_TIME_8H: timer_state = TIMER_8H; timer_counter = 0; break;
        case RF433_CMD_TIME_OFF: timer_state = TIMER_OFF; timer_counter = 0; break;
        case RF433_CMD_DIM_DOWN: if (dim_level > 0) dim_level--; break;
        case RF433_CMD_DIM_UP: if (dim_level < 3) dim_level++; break;
        case RF433_CMD_MODE_1: current_effect = EFFECT_SLOW_FLASH; effect_new_execute(EFFECT_SLOW_FLASH); break;
        case RF433_CMD_MODE_2: current_effect = EFFECT_SLOW_FLASH; effect_new_execute(EFFECT_SLOW_FLASH); break;
        case RF433_CMD_MODE_3: current_effect = EFFECT_FAST_FLASH; effect_new_execute(EFFECT_FAST_FLASH); break;
        case RF433_CMD_MODE_4: current_effect = EFFECT_BREATH_10COLOR; effect_new_execute(EFFECT_BREATH_10COLOR); break;
        case RF433_CMD_MODE_5: current_effect = EFFECT_SLOW_RAINBOW; effect_new_execute(EFFECT_SLOW_RAINBOW); break;
        case RF433_CMD_MODE_6: current_effect = EFFECT_FAST_RAINBOW; effect_new_execute(EFFECT_FAST_RAINBOW); break;
        case RF433_CMD_MODE_7: current_effect = EFFECT_POLICE_NEW; effect_new_execute(EFFECT_POLICE_NEW); break;
        case RF433_CMD_MODE_8: current_effect = EFFECT_MARQUEE_NEW; effect_new_execute(EFFECT_MARQUEE_NEW); break;
        case RF433_CMD_RESET:
            current_effect = EFFECT_SLOW_FLASH;
            g_color_index = 0;
            dim_level = 0;
            timer_state = TIMER_OFF;
            timer_counter = 0;
            power_state = 1;
            battery_clear_protect();
            effect_new_execute(EFFECT_SLOW_FLASH);
            break;
    }
    power_reset_idle_counter();
}

void System_Init(void) {
    GIE = 0;
    system_clock_init();
    gpio_init();

#if ENABLE_BATTERY_MONITOR
    battery_adc_init();
    battery_update_brightness_limit();
#endif

#if ENABLE_CDS_SENSOR
    cds_adc_init();
#endif

#if ENABLE_RF433_CONTROL
    rf433_init();
    rf433_turn_on();
#endif

#if ENABLE_POWER_MANAGEMENT
    power_manager_init();
#endif

    effect_new_execute(EFFECT_SLOW_FLASH);

    GIE = 1;
    PEIE = 1;
}

void main(void) {
    System_Init();
    unsigned char update = 0, bat_cnt = 0, cds_cnt = 0, low_cnt = 0;
    unsigned char bat_protect_flag = 0;

    while (1) {
        asm("clrwdt");
        key_scan();

#if ENABLE_RF433_CONTROL
        if (rf433_has_command()) {
            rf433_process_command();
        }
        rf433_update_timer();
        if (rf433_timer_expired()) {
            power_state = 0;
        }
#endif

#if ENABLE_VIBRATION_SENSOR
        vibration_check();
        if (vibration_detected()) {
            if (!power_state && !battery_check_protection()) {
                power_state = 1;
                battery_clear_protect();
                effect_new_execute(current_effect);
            }
            power_reset_idle_counter();
        }
#endif

#if ENABLE_BATTERY_MONITOR
        if (++bat_cnt >= (BATTERY_CHECK_INTERVAL / 10)) {
            bat_cnt = 0;
            battery_update_brightness_limit();
            battery_fade_counter = 0;
        }
        battery_fade_update();

        if (battery_check_protection()) {
            if (!bat_protect_flag) {
                bat_protect_flag = 1;
                power_state = 0;
                unsigned char i;
                for (i = 0; i < LED_COUNT; i++) leds[i].r = leds[i].g = leds[i].b = 0;
                ws2812_update_RGB(leds, LED_COUNT);
            }
        } else if (bat_protect_flag) {
            bat_protect_flag = 0;
        }

        BatteryStatus_t status = battery_get_status();
        if (status == BATTERY_LOW && ++low_cnt >= 50) {
            low_cnt = 0;
            leds[0].r = (leds[0].r == 0) ? 100 : 0;
            leds[0].g = leds[0].b = 0;
        }
#endif

#if ENABLE_CDS_SENSOR
        if (++cds_cnt >= (CDS_CHECK_INTERVAL / 10)) {
            cds_cnt = 0;
            cds_update();
        }
#endif

        if (++update >= 10) {
            update = 0;

            if (power_state && !bat_protect_flag) {
                unsigned char i;
                effects_new_update();
                for (i = 0; i < LED_COUNT; i++) {
                    leds[i].r = apply_limits(leds[i].r);
                    leds[i].g = apply_limits(leds[i].g);
                    leds[i].b = apply_limits(leds[i].b);
                }
                ws2812_update_RGB(leds, LED_COUNT);
            }

#if ENABLE_POWER_MANAGEMENT
            power_update_idle_counter();
#endif
        }

#if ENABLE_POWER_MANAGEMENT
        if (!power_state || power_get_state() == POWER_STATE_SLEEP_AUTO) {
            delay_ms(100);
            power_enter_sleep(SLEEP_MODE_SLEEP);
            System_Init();
        }
#endif

        delay_ms(1);
    }
}