#include <sc.h>
#include "vibration.h"

// 震动检测参数
// 规格: 200ms内检测到5次低电平触发
#define VIBR_SAMPLE_RATE     40     // 采样间隔 (ms)
#define VIBR_WINDOW          200    // 检测窗口时间 (ms)
#define VIBR_TRIGGER_COUNT   5      // 触发次数阈值 (200ms内5次)
#define VIBR_DEBOUNCE        200    // 触发后冷却时间 (ms)

volatile unsigned char vibration_wakeup = 0;

static unsigned int vibr_timer = 0;
static unsigned int vibr_debounce_timer = 0;
static unsigned char low_count = 0;       // 窗口内有效低电平计数
static unsigned char last_reading = 1;   // 上次采样值

// 初始化
void vibration_init(void) {
    ANSEL1 &= ~(1 << PIN_VIBR_BIT);
    TRISB |= (1 << PIN_VIBR_BIT);

    vibr_timer = 0;
    vibr_debounce_timer = 0;
    vibration_wakeup = 0;
    low_count = 0;
    last_reading = 1;
}

// 检测调用 (每40ms调用一次)
void vibration_check(void) {
    unsigned char current = PIN_VIBR_READ();

    // 冷却中，跳过
    if (vibr_debounce_timer > 0) {
        vibr_debounce_timer++;
        if (vibr_debounce_timer >= VIBR_DEBOUNCE) {
            vibr_debounce_timer = 0;
        }
        return;
    }

    // 有效低电平检测：
    // 震动时信号为低，但50Hz键波是交流，会交替出现高低
    // 只有本次低且上次也低，才认为是有效低电平（消抖）
    if (current == 0 && last_reading == 0) {
        low_count++;
    }
    last_reading = current;

    vibr_timer++;
    if (vibr_timer >= VIBR_SAMPLE_RATE) {
        vibr_timer = 0;

        // 达到触发阈值
        if (low_count >= VIBR_TRIGGER_COUNT) {
            vibration_wakeup = 1;
            vibr_debounce_timer = 1;
        }

        // 窗口结束，清零计数
        low_count = 0;
    }
}

// 获取震动状态 (需清除)
unsigned char vibration_detected(void) {
    unsigned char s = vibration_wakeup;
    vibration_wakeup = 0;
    return s;
}