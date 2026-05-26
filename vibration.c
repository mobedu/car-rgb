#include <sc.h>
#include "vibration.h"

// 震动检测参数
// 规格: 200ms内检测到5次低电平触发
#define VIBR_SAMPLE_RATE     40     // 采样间隔 (调用次数)
#define VIBR_TRIGGER_COUNT   5      // 触发次数阈值
#define VIBR_DEBOUNCE_CALLS  5      // 触发后冷却(调用次数)

volatile unsigned char vibration_wakeup = 0;

static unsigned int vibr_sample_counter = 0;
static unsigned int vibr_debounce_counter = 0;
static unsigned char low_count = 0;
static unsigned char last_reading = 1;
static unsigned char vibr_initialized = 0;

// 初始化
void vibration_init(void) {
    ANSEL1 &= ~(1 << PIN_VIBR_BIT);
    TRISB |= (1 << PIN_VIBR_BIT);

    vibr_sample_counter = 0;
    vibr_debounce_counter = 0;
    vibration_wakeup = 0;
    low_count = 0;
    last_reading = PIN_VIBR_READ();  // 初始化读取实际引脚状态
    vibr_initialized = 1;
}

// 检测调用 (由主循环每次迭代调用一次)
void vibration_check(void) {
    if (!vibr_initialized) return;

    // 冷却中
    if (vibr_debounce_counter > 0) {
        vibr_debounce_counter++;
        if (vibr_debounce_counter >= VIBR_DEBOUNCE_CALLS) {
            vibr_debounce_counter = 0;
        }
        return;
    }

    // 读取传感器
    unsigned char current = PIN_VIBR_READ();

    // 只检测下降沿（高→低），持续低电平不计入
    if (last_reading == 1 && current == 0) {
        low_count++;
    } else if (current == 1) {
        // 高电平时清零计数
        low_count = 0;
    }
    last_reading = current;

    // 每40ms检查一次（约每40次调用，因为主循环delay_ms(1)）
    vibr_sample_counter++;
    if (vibr_sample_counter >= VIBR_SAMPLE_RATE) {
        vibr_sample_counter = 0;

        if (low_count >= VIBR_TRIGGER_COUNT) {
            vibration_wakeup = 1;
            vibr_debounce_counter = 1;
        }

        low_count = 0;
    }
}

// 获取震动状态
unsigned char vibration_detected(void) {
    unsigned char s = vibration_wakeup;
    vibration_wakeup = 0;
    return s;
}
// v1.04 - 修复持续低电平误触发