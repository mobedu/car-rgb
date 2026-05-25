#include <sc.h>
#include "vibration.h"

volatile unsigned char vibration_wakeup = 0;

// 采样缓冲区
static unsigned char vibr_samples[VIBR_SAMPLE_COUNT];
static unsigned char vibr_sample_idx = 0;
static unsigned char vibr_sample_cnt = 0;
static unsigned int vibr_timer = 0;

// 初始化
void vibration_init(void) {
    unsigned char i;
    // 配置RB2为输入
    ANSEL1 &= ~(1 << PIN_VIBR_BIT);
    TRISB |= (1 << PIN_VIBR_BIT);

    // 初始化缓冲区
    for (i = 0; i < VIBR_SAMPLE_COUNT; i++) {
        vibr_samples[i] = 1;
    }
    vibr_sample_idx = 0;
    vibr_sample_cnt = 0;
    vibr_timer = 0;
    vibration_wakeup = 0;
}

// 检测调用 (建议每40ms调用一次，200ms内可采样5次)
void vibration_check(void) {
    unsigned char current = PIN_VIBR_READ();
    unsigned char i;
    unsigned char trigger_count = 0;

    // 记录采样值
    vibr_samples[vibr_sample_idx] = current;
    vibr_sample_idx++;
    if (vibr_sample_idx >= VIBR_SAMPLE_COUNT) {
        vibr_sample_idx = 0;
    }
    if (vibr_sample_cnt < VIBR_SAMPLE_COUNT) {
        vibr_sample_cnt++;
    }

    // 统计下降沿触发次数 (从高到低的跳变)
    for (i = 0; i < vibr_sample_cnt - 1; i++) {
        if (vibr_samples[i] == 1 && vibr_samples[i + 1] == 0) {
            trigger_count++;
        }
    }

    // 检查是否达到阈值
    if (vibr_sample_cnt >= VIBR_SAMPLE_COUNT && trigger_count >= VIBR_THRESHOLD) {
        vibration_wakeup = 1;
        // 清除缓冲区，防止重复触发
        for (i = 0; i < VIBR_SAMPLE_COUNT; i++) {
            vibr_samples[i] = 1;
        }
        vibr_sample_cnt = 0;
        vibr_sample_idx = 0;
    }
}

// 获取震动状态 (需清除)
unsigned char vibration_detected(void) {
    unsigned char s = vibration_wakeup;
    vibration_wakeup = 0;
    return s;
}