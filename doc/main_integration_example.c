// 集成示例 main.c (仅展示新增部分)

// ========== 新增包含 ==========
#include "battery.h"
#include "rf433.h"
#include "vibration.h"
#include "power.h"
#include "iservices.h"

// ========== 系统初始化函数 ==========
void System_Init(void) {
    // 关闭中断
    GIE = 0;

    // 系统时钟初始化
    system_clock_init();

    // GPIO 初始化
    ws2812_gpio_init();

    // 上拉电阻
    WPUA |= (1 << 0);

    // 外设初始化
#if ENABLE_BATTERY_MONITOR
    battery_adc_init();
    battery_update_brightness_limit();
#endif

#if ENABLE_POWER_MANAGEMENT
    power_manager_init();
#endif

    // 效果初始化
#if USE_NEW_EFFECTS
    effect_new_init();
#else
    effect_init();
#endif

    // 开启中断
    GIE = 1;
    PEIE = 1;
}

// ========== RF433 命令处理 ==========
void rf433_process_command(void) {
    unsigned char cmd = rf433_get_command();

    switch (cmd) {
        case RF433_CMD_POWER_ON:
            // 开机
            power_state = 1;
            power_wakeup_handler(WAKEUP_SOURCE_RF433);
            break;

        case RF433_CMD_POWER_OFF:
            // 关机
            power_state = 0;
            unsigned char i;
            for (i = 0; i < LED_COUNT; i++) {
                leds[i].r = 0;
                leds[i].g = 0;
                leds[i].b = 0;
            }
            ws2812_update_RGB(leds, LED_COUNT);
            break;

        case RF433_CMD_EFFECT_NEXT:
            // 下一个效果
#if USE_NEW_EFFECTS
            EffectMode_t next_mode = (current_effect + 1) % 7;
            effect_new_execute(next_mode);
#else
            EffectMode_t next_mode = (current_effect + 1) % EFFECT_COUNT;
            effect_execute(next_mode);
#endif
            break;

        case RF433_CMD_EFFECT_PREV:
            // 上一个效果
#if USE_NEW_EFFECTS
            EffectMode_t prev_mode = (current_effect + 6) % 7;
            effect_new_execute(prev_mode);
#else
            EffectMode_t prev_mode = (current_effect + EFFECT_COUNT - 1) % EFFECT_COUNT;
            effect_execute(prev_mode);
#endif
            break;

        case RF433_CMD_COLOR_NEXT:
            // 下一个颜色 (闪烁模式)
#if USE_NEW_EFFECTS
            if (current_effect == EFFECT_SLOW_FLASH || current_effect == EFFECT_FAST_FLASH) {
                g_color_index = (g_color_index + 1) % 10;
                effect_new_execute(current_effect);
            }
#endif
            break;

        default:
            break;
    }

    // 重置空闲计数器
    power_reset_idle_counter();
}

// ========== 主函数修改示例 ==========
void main(void) {
    // 初始化系统
    System_Init();

    // 循环变量
    unsigned int update_counter = 0;
    unsigned int battery_counter = 0;
    unsigned char last_power_state = 1;

    while (1) {
        asm("clrwdt");

        // 按键扫描
        key_scan();

        // RF433 命令处理
#if ENABLE_RF433_RECEIVER
        if (rf433_has_command()) {
            rf433_process_command();
        }
#endif

        // 震动检测
#if ENABLE_VIBRATION_SENSOR
        if (vibration_detected()) {
            // 震动唤醒后的简单反馈
            unsigned char i;
            for (i = 0; i < LED_COUNT; i++) {
                leds[i].r = battery_apply_limit(50);
                leds[i].g = battery_apply_limit(50);
                leds[i].b = battery_apply_limit(50);
            }
            ws2812_update_RGB(leds, LED_COUNT);
            delay_ms(500);
            effect_new_execute(current_effect);

            power_reset_idle_counter();
        }
#endif

        // 电池电压检测
#if ENABLE_BATTERY_MONITOR
        battery_counter++;
        if (battery_counter >= (BATTERY_CHECK_INTERVAL / 10)) {
            battery_counter = 0;
            battery_update_brightness_limit();

            // 电池状态 LED 指示 (可选)
            BatteryStatus_t status = battery_get_status();
            if (status == BATTERY_CRITICAL) {
                // 闪烁红色指示低电量
                static unsigned char low_bat_counter = 0;
                low_bat_counter++;
                if (low_bat_counter >= 50) {
                    low_bat_counter = 0;
                    // 在第一个 LED 上显示低电量
                    leds[0].r = (leds[0].r == 0) ? 100 : 0;
                    leds[0].g = 0;
                    leds[0].b = 0;
                }
            }
        }
#endif

        // 效果更新
        update_counter++;
        if (update_counter >= 10) {
            update_counter = 0;

            if (power_state) {
#if USE_NEW_EFFECTS
                effects_new_update();
#else
                effects_update();
#endif

                // 应用电池亮度限制
                unsigned char i;
                for (i = 0; i < LED_COUNT; i++) {
                    leds[i].r = battery_apply_limit(leds[i].r);
                    leds[i].g = battery_apply_limit(leds[i].g);
                    leds[i].b = battery_apply_limit(leds[i].b);
                }

                ws2812_update_RGB(leds, LED_COUNT);
            }

            // 更新空闲计数器
#if ENABLE_POWER_MANAGEMENT
            power_update_idle_counter();
#endif
        }

        // 检查是否需要进入睡眠
#if ENABLE_POWER_MANAGEMENT
        if (!power_state || power_get_state() == POWER_STATE_SLEEP_AUTO) {
            // 短暂延迟后进入睡眠
            delay_ms(100);

            // 进入睡眠模式
            power_enter_sleep(SLEEP_MODE_SLEEP);

            // 唤醒后重新初始化
            System_Init();
        }
#endif

        delay_ms(1);
    }
}