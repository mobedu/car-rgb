#include <sc.h>
#include "config.h"
#include "ws2812.h"
#include "key.h"
#include "effects.h"
#include "power.h"
#include "rf433.h"
#include "vibration.h"

unsigned char power_state = 1;
static unsigned char lights_on = 1;  // 遥控OFF只关灯，不关机
static unsigned char key_pressed = 0;
static unsigned int  key_press_counter = 0;
static unsigned int  idle_counter = 0;        // 无活动计时器 (30秒后关机)

// 电池ADC读取间隔计数器
static unsigned int battery_check_counter = 0;
static unsigned int battery_adc_value = 1750;  // 默认~4.1V
static unsigned char battery_target_brightness = 255;  // 目标亮度(基于电压)
static unsigned char current_battery_brightness = 255;  // 当前亮度(缓降中)
static unsigned int brightness_fade_counter = 0;         // 亮度衰减计时器
static unsigned char battery_low_voltage_lock = 0;         // 低电压锁定标志

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
    adc_init();
    rf433_init();
    vibration_init();
    effects_init();

    // 初始化电池亮度缓降
    battery_check_counter = 0;
    battery_adc_value = battery_read_adc();
    battery_target_brightness = get_battery_brightness(battery_adc_value);
    brightness_fade_counter = 0;
    current_battery_brightness = battery_target_brightness;
    max_brightness_limit = current_battery_brightness;

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
                    // 检查低电压锁定
                    if (battery_low_voltage_lock) {
                        // 低电压锁定中,禁止开灯
                        break;
                    }
                    lights_on = 1;
                    idle_counter = 0;
                    if (!power_state) {
                        power_state = 1;
                        PIN_LED_POWER_ON();
                    }
                    break;

                case RF_CMD_OFF:
                    // 只关灯，不关机（保持RF接收）
                    lights_on = 0;
                    idle_counter = 0;
                    power_off_leds(leds);
                    ws2812_update(leds, LED_COUNT);
                    break;

                case RF_CMD_MODE_1:  idle_counter = 0; effects_set_mode(1); break;
                case RF_CMD_MODE_2:  idle_counter = 0; effects_set_mode(2); break;
                case RF_CMD_MODE_3:  idle_counter = 0; effects_set_mode(3); break;
                case RF_CMD_MODE_4:  idle_counter = 0; effects_set_mode(4); break;
                case RF_CMD_MODE_5:  idle_counter = 0; effects_set_mode(5); break;
                case RF_CMD_MODE_6:  idle_counter = 0; effects_set_mode(6); break;
                case RF_CMD_MODE_7:  idle_counter = 0; effects_set_mode(7); break;
                case RF_CMD_MODE_8:  idle_counter = 0; effects_set_mode(8); break;

                case RF_CMD_DIM_UP:   idle_counter = 0; effects_brightness_up();   break;
                case RF_CMD_DIM_DOWN: idle_counter = 0; effects_brightness_down(); break;

                case RF_CMD_RESET:
                    idle_counter = 0;
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

        // ===== 震动检测 =====
#if ENABLE_VIBRATION_SENSOR
        vibration_check();
        if (vibration_detected()) {
            // 检查低电压锁定,锁定时不响应震动唤醒
            if (battery_low_voltage_lock) {
                idle_counter = 0;
            } else {
                idle_counter = 0;  // 重置无活动计时器
                // 震动唤醒：开灯
                if (!power_state) {
                    power_state = 1;
                    lights_on = 1;
                    PIN_LED_POWER_ON();
                    system_clock_init();
                    gpio_init();
                    rf433_init();
                    effects_init();
                } else {
                    // 已开机则切回模式1
                    lights_on = 1;
                    effects_set_mode(1);
                }
            }
        }
#endif

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
                    if (!power_state) {
                        // 开机时检查低电压锁定
                        if (battery_low_voltage_lock) {
                            unsigned int cur_adc = battery_read_adc();
                            if (cur_adc >= 1325) {
                                // 电压已恢复,清除锁定并开机
                                battery_low_voltage_lock = 0;
                                power_state = 1;
                                lights_on = 1;
                                PIN_LED_POWER_ON();
                                system_clock_init();
                                gpio_init();
                                while (PIN_KEY_READ() == 0);
                                key_pressed = 0;
                                key_press_counter = 0;
                            } else {
                                // 电压仍低,不响应开机
                                while (PIN_KEY_READ() == 0);
                                key_pressed = 0;
                                key_press_counter = 0;
                            }
                        } else {
                            power_state = 1;
                            lights_on = 1;
                            PIN_LED_POWER_ON();
                            system_clock_init();
                            gpio_init();
                        }
                    } else {
                        power_state = 0;
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
                        idle_counter = 0;
                    }
                }
                key_pressed = 0;
                key_press_counter = 0;
            }
        }

        // ===== 效果更新 + 刷新LED =====
        // 每5ms同步更新，更快发送减少中断干扰
        if (power_state && lights_on) {
            if (++frame_cnt >= 5) {
                frame_cnt = 0;
                effects_update();
                ws2812_update(leds, LED_COUNT);
            }
        }

        delay_ms(1);

        // ===== 无活动30秒自动关机 =====
        if (power_state && lights_on) {
            idle_counter++;
            // 30秒 = 30000ms ≈ 30000次delay(1)
            if (idle_counter >= 30000) {
                // 自动关机
                power_state = 0;
                lights_on = 0;
                power_off_leds(leds);
                ws2812_update(leds, LED_COUNT);
                PIN_LED_POWER_OFF();
            }
        }

        // ===== 电池电压检测 & 动态亮度 =====
#if ENABLE_BATTERY_MONITOR
        if (power_state && lights_on) {
            // 每1秒读取电池电压,获取目标亮度
            if (++battery_check_counter >= 1000) {
                battery_check_counter = 0;
                battery_adc_value = battery_read_adc();
                battery_target_brightness = get_battery_brightness(battery_adc_value);

                // 低电压保护逻辑 (ADC: 2.7V=1152, 3.1V=1325)
                if (battery_low_voltage_lock) {
                    // 已锁定,只有电压>=3.1V才能解锁
                    if (battery_adc_value >= 1325) {
                        battery_low_voltage_lock = 0;  // 解除锁定
                    }
                } else {
                    // 未锁定,电压<2.7V则锁定
                    if (battery_adc_value < 1152) {
                        battery_low_voltage_lock = 1;  // 进入锁定
                    }
                }
            }

            // 亮度缓降: 每5秒调整1亮度,5分钟≈300秒可调整60亮度
            brightness_fade_counter++;
            if (brightness_fade_counter >= 5) {
                brightness_fade_counter = 0;
                if (current_battery_brightness > battery_target_brightness) {
                    current_battery_brightness--;
                } else if (current_battery_brightness < battery_target_brightness) {
                    current_battery_brightness++;
                }
            }
            max_brightness_limit = current_battery_brightness;
        }
#endif

        // ===== 太阳能板光线检测 =====
#if ENABLE_CDS_SENSOR
        solar_auto_control();
        // 环境光线太亮时，禁止开灯
        if (power_state && lights_on && !solar_auto_enabled) {
            power_off_leds(leds);
            ws2812_update(leds, LED_COUNT);
        }
#endif
    }
}
