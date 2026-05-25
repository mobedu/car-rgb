#include <sc.h>
#include "config.h"
#include "ws2812.h"
#include "key.h"
#include "effects.h"
#include "power.h"
#include "rf433.h"

unsigned char power_state = 1;
static unsigned char lights_on = 1;  // 遥控OFF只关灯，不关机
static unsigned char key_pressed = 0;
static unsigned int  key_press_counter = 0;

static void system_clock_init(void) {
    OSCCON = 0x70;
}

static void gpio_init(void) {
    ANSEL0 = 0;
    ANSEL1 = 0;

    // RA0: RF数据，输入
    TRISA |= (1 << 0);
    ANSEL0 &= ~(1 << 0);

    // RA1: LED供电，输出高（开）
    TRISA &= ~(1 << PIN_LED_POWER_BIT);
    PIN_LED_POWER_ON();

    // RB7: WS2812数据，输出低
    TRISB &= ~(1 << PIN_WS2812B_BIT);
    PORTB &= ~(1 << PIN_WS2812B_BIT);

    // RB4: RF SHUT，输出低（开）
    TRISB &= ~(1 << PIN_SHUT_BIT);
    ANSEL1 &= ~(1 << PIN_SHUT_BIT);
    PIN_SHUT_LOW();

    // RB3: 调试引脚，输出低 (Timer2频率输出)
    TRISB &= ~(1 << PIN_DEBUG_BIT);
    ANSEL1 &= ~(1 << PIN_DEBUG_BIT);
    PORTB &= ~(1 << PIN_DEBUG_BIT);

    // 按键引脚: RA5
    TRISA |= (1 << 5);
    WPUA |= (1 << 5);

    // ADC引脚输入
    TRISB |= (1 << 0);   // RB0
    TRISB |= (1 << 2);   // RB2
    TRISA |= (1 << 2);   // RA2
    TRISA |= (1 << 3);   // RA3
}

static void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 1333; j++) asm("nop");
    }
}

RGB_t leds[LED_COUNT];

void interrupt ISR(void) {
    asm("clrwdt");
    if (TMR2IF) {
        TMR2IF = 0;
        rf433_timer_isr();
    }
}

void main(void) {
    unsigned char frame_cnt = 0;

    INTCON &= ~(1 << 7);
    system_clock_init();
    gpio_init();
    rf433_init();
    effects_init();

    power_state = 1;
    effects_update();
    ws2812_update(leds, LED_COUNT);

    INTCON |= (1 << 7);
    INTCON |= (1 << 6);   // PEIE=1 for Timer2

    while (1) {
        asm("clrwdt");

        // ===== RF命令处理 =====
        if (rf433_has_command()) {
            unsigned char cmd = rf433_get_command();
            rf433_clear_command();

            switch (cmd) {
                case RF_CMD_ON:
                    lights_on = 1;
                    if (!power_state) {
                        power_state = 1;
                        PIN_LED_POWER_ON();
                    }
                    break;

                case RF_CMD_OFF:
                    // 只关灯，不关机（保持RF接收）
                    lights_on = 0;
                    power_off_leds(leds);
                    ws2812_update(leds, LED_COUNT);
                    break;

                case RF_CMD_MODE_1:  effects_set_mode(1); break;
                case RF_CMD_MODE_2:  effects_set_mode(2); break;
                case RF_CMD_MODE_3:  effects_set_mode(3); break;
                case RF_CMD_MODE_4:  effects_set_mode(4); break;
                case RF_CMD_MODE_5:  effects_set_mode(5); break;
                case RF_CMD_MODE_6:  effects_set_mode(6); break;
                case RF_CMD_MODE_7:  effects_set_mode(7); break;
                case RF_CMD_MODE_8:  effects_set_mode(8); break;

                case RF_CMD_DIM_UP:   effects_brightness_up();   break;
                case RF_CMD_DIM_DOWN: effects_brightness_down(); break;

                case RF_CMD_RESET:
                    color_index = 9;
                    effects_set_mode(1);
                    break;

                // 定时命令暂不实现
                case RF_CMD_TIME_4H:
                case RF_CMD_TIME_6H:
                case RF_CMD_TIME_8H:
                case RF_CMD_TIME_OFF:
                    break;

                default:
                    break;
            }
        }

        // ===== 按键扫描 =====
        if (PIN_KEY_READ() == 0) {
            if (!key_pressed) {
                delay_ms(20);
                if (PIN_KEY_READ() == 0) {
                    key_pressed = 1;
                    key_press_counter = 0;
                }
            } else {
                if (key_press_counter < 255) {
                    key_press_counter++;
                }
                if (key_press_counter == 150) {
                    // 长按2秒: 开关机
                    power_state = !power_state;
                    lights_on = power_state;
                    if (power_state) {
                        PIN_LED_POWER_ON();
                        system_clock_init();
                        gpio_init();
                    } else {
                        power_off_leds(leds);
                        ws2812_update(leds, LED_COUNT);
                        PIN_LED_POWER_OFF();
                    }
                    while (PIN_KEY_READ() == 0);
                    key_pressed = 0;
                    key_press_counter = 0;
                }
            }
        } else {
            if (key_pressed) {
                if (key_press_counter < 150) {
                    // 短按: 切颜色
                    if (power_state && lights_on) {
                        effects_next_color();
                    }
                }
                key_pressed = 0;
                key_press_counter = 0;
            }
        }

        // ===== 效果更新 + 刷新LED =====
        if (power_state && lights_on) {
            effects_update();
            if (++frame_cnt >= 10) {
                frame_cnt = 0;
                ws2812_update(leds, LED_COUNT);
            }
        }

        delay_ms(1);
    }
}
