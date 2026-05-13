#include <sc.h>
#include "config.h"

// 16MHz, 2T模式, 1指令 = 125ns
// WS2812时序要求:
// 1码: 高 700-900ns (5.6-7.2 NOP) -> 6-7 NOP
//      低 200-400ns (1.6-3.2 NOP) -> 2-3 NOP
// 0码: 高 200-400ns (1.6-3.2 NOP) -> 2-3 NOP
//      低 600-800ns (4.8-6.4 NOP) -> 5-6 NOP
// 总周期: ~1250ns

// 可配置的时序参数（NOP数量）
static uint8_t timing_one_high = 6;
static uint8_t timing_one_low = 2;
static uint8_t timing_zero_high = 2;
static uint8_t timing_zero_low = 6;

// 设置时序参数
void ws2812_set_timing(uint8_t one_h, uint8_t one_l, uint8_t zero_h, uint8_t zero_l) {
    timing_one_high = one_h;
    timing_one_low = one_l;
    timing_zero_high = zero_h;
    timing_zero_low = zero_l;
}

// 发送单个bit（内联优化）
static inline void send_bit_inline(uint8_t bit) {
    RB1 = 1;

    if (bit) {
        // 1码
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        // RB1 = 0;
        asm("nop");
        // RB1 = 0;
        // 低电平
    } else {
        // 0码
        asm("nop"); asm("nop");
        // RB1 = 0;
        // 低电平
    }

    RB1 = 0;

    if (bit) {
        asm("nop");
    } else {
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    }
}

void ws2812_send_byte(uint8_t data) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        if (data & 0x80) {
            // 发送1码
            RB1 = 1;
            asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
            RB1 = 0;
            asm("nop"); asm("nop");
        } else {
            // 发送0码
            RB1 = 1;
            asm("nop"); asm("nop");
            RB1 = 0;
            asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        }
        data <<= 1;
    }
}

void ws2812_reset(void) {
    RB1 = 0;
    _delay(60);
}

void ws2812_init(void) {
    ANSEL1 &= ~(1 << 1);
    TRISB1 = 0;
    RB1 = 0;
}

void ws2812_set_all(uint8_t r, uint8_t g, uint8_t b) {
    ws2812_send_byte(g);
    ws2812_send_byte(r);
    ws2812_send_byte(b);
    ws2812_reset();
}

// 获取当前时序配置（用于调试）
void ws2812_get_timing(uint8_t *one_h, uint8_t *one_l, uint8_t *zero_h, uint8_t *zero_l) {
    *one_h = timing_one_high;
    *one_l = timing_one_low;
    *zero_h = timing_zero_high;
    *zero_l = timing_zero_low;
}
