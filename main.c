#include <sc.h>
#include "config.h"
#include "ws2812.h"
#include "key.h"
#include "effects.h"
#include "power.h"
#include "rf433.h"
#include "timer.h"
#include "vibration.h"

unsigned char power_state = 1;
static unsigned char lights_on = 1;  // 遥控OFF只关灯，不关机
static unsigned char lights_off_by_user = 0;  // 用户手动关灯标志
static unsigned char lights_off_by_timer = 0;  // 遥控定时关灯标志
static unsigned char key_pressed = 0;
static unsigned int  key_press_counter = 0;
static unsigned char last_brightness = 0;
static unsigned char timer_off_indicator = 0;  // 定时取消指示标志

// 定时功能 (10秒/30秒/60秒，便于测试)
static unsigned int timer_countdown = 0;      // 倒计时计数器 (每秒+1)
static unsigned int timer_target = 0;         // 已设置的定时秒数
#define TIMER_MAX_SECONDS timer_target        // 目标秒数

// 无震动定时功能 (独立于遥控器定时)
static unsigned int no_vibr_target = 30;     // 无震动目标30秒

static void system_clock_init(void) {
    OSCCON = 0x70;
	// debug hz
	__delay_ms(100);
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
    if (T0IF) {
        T0IF = 0;
        timer0_tick();
    }
}

void main(void) {
    unsigned char frame_cnt = 0;

    INTCON &= ~(1 << 7);
    system_clock_init();
    gpio_init();
    rf433_init();
    timer0_init();
    vibration_init();
    effects_init();

    power_state = 1;
    effects_update();
    ws2812_update(leds, LED_COUNT);

    INTCON |= (1 << 7);  // GIE=1
    INTCON |= (1 << 6);  // PEIE=1 for Timer2/Timer0
    INTCON |= (1 << 5);  // T0IE=1 Enable Timer0 interrupt

    while (1) {
        asm("clrwdt");

        // ===== RF命令处理 =====
        if (rf433_has_command()) {
            unsigned char cmd = rf433_get_command();
            rf433_clear_command();

            switch (cmd) {
                case RF_CMD_ON:
                    lights_on = 1;
                    lights_off_by_user = 0;
                    lights_off_by_timer = 0;
                    PIN_LED_POWER_ON();
                    if (!power_state) {
                        power_state = 1;
                    }
                    no_vibr_timer_seconds = 0;  // 重置无震动计时
                    break;

                case RF_CMD_OFF:
                    // 关灯并关闭LED供电（低功耗）
                    lights_on = 0;
                    lights_off_by_user = 1;
                    power_off_leds(leds);
                    ws2812_update(leds, LED_COUNT);
                    PIN_LED_POWER_OFF();
                    timer_target = 0;
                    timer_countdown = 0;
                    no_vibr_timer_seconds = 0;  // 取消无震动定时
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
                    timer_target = 0;  // 取消定时
                    timer_countdown = 0;
                    timer_triggered = 0;
                    break;

                // 定时命令 (10秒/30秒/60秒，便于测试)
                case RF_CMD_TIME_4H: timer_target = 10; timer_countdown = 0; timer_triggered = 0; break;
                case RF_CMD_TIME_6H: timer_target = 30; timer_countdown = 0; timer_triggered = 0; break;
                case RF_CMD_TIME_8H: timer_target = 60; timer_countdown = 0; timer_triggered = 0; break;
                case RF_CMD_TIME_OFF:
                    timer_target = 0;
                    timer_countdown = 0;
                    timer_triggered = 0;
                    timer_off_indicator = 100;  // 约1秒指示
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
                    no_vibr_timer_seconds = 0;  // 重置无震动计时
                    if (power_state) {
                        // 开机: 恢复系统时钟和GPIO，重新使能外设
                        system_clock_init();
                        gpio_init();
                        lights_off_by_timer = 0;  // 开机清除定时关灯标志
                        // gpio_init已设置RA1=1
                    } else {
                        // 关机: 先关灯，再关RA1电源
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
                    // 短按: 模式1切颜色，其他模式切到模式1(常亮)
                    if (power_state && lights_on) {
                        effects_button_short_press();
                    }
                }
                key_pressed = 0;
                key_press_counter = 0;
            }
        }

        // ===== 震动检测 =====
        vibration_check();
        if (vibration_detected()) {
            // 检测到震动，开灯或重置无震动计时
            if (!lights_on && !lights_off_by_timer) {
                lights_on = 1;
                lights_off_by_user = 0;
                PIN_LED_POWER_ON();
            }
            no_vibr_timer_seconds = 0;
        }

        // ===== 无震动定时处理 =====
        if (lights_on) {
            if (no_vibr_timer_seconds >= no_vibr_target) {
                // 30秒无震动，关灯
                lights_on = 0;
                power_off_leds(leds);
                ws2812_update(leds, LED_COUNT);
                PIN_LED_POWER_OFF();
                no_vibr_timer_seconds = 0;
            }
        }

        // ===== 定时取消指示 =====
        if (timer_off_indicator > 0) {
            timer_off_indicator--;
            leds[LED_COUNT-1].r = 255;
            leds[LED_COUNT-1].g = 0;
            leds[LED_COUNT-1].b = 0;
        }

        // ===== 效果更新 + 刷新LED =====
        if (power_state && lights_on) {
            if (effects_get_brightness() != last_brightness) {
                effects_update();
                last_brightness = effects_get_brightness();
                ws2812_update(leds, LED_COUNT);
            } else {
                effects_update();
                if (++frame_cnt >= 10) {
                    frame_cnt = 0;
                    ws2812_update(leds, LED_COUNT);
                }
            }
        }

        // ===== 定时器处理 =====
        if (timer_target > 0) {
            if (timer_triggered) {
                timer_triggered = 0;
                timer_countdown++;
                if (timer_countdown >= TIMER_MAX_SECONDS) {
                    // 时间到，关闭灯
                    lights_on = 0;
                    lights_off_by_timer = 1;  // 标记为定时关灯
                    power_off_leds(leds);
                    ws2812_update(leds, LED_COUNT);
                    PIN_LED_POWER_OFF();
                    timer_target = 0;
                    timer_countdown = 0;
                }
            }
        } else {
            timer_triggered = 0;  // 清除标志
            timer_countdown = 0;    // 额外清除countdown
        }

        delay_ms(1);
    }
}
