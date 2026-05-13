#ifndef __TEST_WS2812_TIMING_H
#define __TEST_WS2812_TIMING_H

#include <sc.h>
#include "config.h"

// 时序配置结构
struct TimingConfig {
    uint8_t one_high;
    uint8_t one_low;
    uint8_t zero_high;
    uint8_t zero_low;
};

// 测试函数
void test_ones(void);
void test_zeros(void);
void test_pattern_1010(void);
void test_pure_green(void);
void test_pure_red(void);
void test_pure_blue(void);
void test_white(void);
void set_timing(uint8_t one_h, uint8_t one_l, uint8_t zero_h, uint8_t zero_l);
void run_timing_test(void);

#endif
