#include <sc.h>
#include "config.h"

// WS2812 时序测试程序
// 用于单独测试0码和1码的时序，方便示波器观察
// 16MHz, 2T模式, 1指令 = 125ns

// 时序参数（NOP数量）
struct TimingConfig {
    uint8_t one_high;    // 1码高电平NOP数
    uint8_t one_low;     // 1码低电平NOP数
    uint8_t zero_high;   // 0码高电平NOP数
    uint8_t zero_low;    // 0码低电平NOP数
};

// 标准WS2812时序参考（16MHz，每NOP=125ns）
// 1码: 高700-900ns (5.6-7.2 NOP) -> 6-7 NOP
//      低200-400ns (1.6-3.2 NOP) -> 2-3 NOP
// 0码: 高200-400ns (1.6-3.2 NOP) -> 2-3 NOP
//      低600-800ns (4.8-6.4 NOP) -> 5-6 NOP

const struct TimingConfig timing_standard = {
    .one_high = 6,   // 750ns
    .one_low = 2,    // 250ns
    .zero_high = 2,  // 250ns
    .zero_low = 6    // 750ns
};

// 当前配置（用于测试调整）
struct TimingConfig current_timing = timing_standard;

// 发送单个bit
void send_bit(uint8_t bit) {
    RB1 = 1;

    if (bit) {
        // 1码
        for (uint8_t i = 1; i < current_timing.one_high; i++) {
            asm("nop");
        }
        RB1 = 0;
        for (uint8_t i = 0; i < current_timing.one_low; i++) {
            asm("nop");
        }
    } else {
        // 0码
        for (uint8_t i = 1; i < current_timing.zero_high; i++) {
            asm("nop");
        }
        RB1 = 0;
        for (uint8_t i = 0; i < current_timing.zero_low; i++) {
            asm("nop");
        }
    }
}

// 连续发送32个1码（用于示波器观察）
void test_ones(void) {
    for (uint8_t i = 0; i < 32; i++) {
        send_bit(1);
    }
    RB1 = 0;
    _delay(60);
}

// 连续发送32个0码（用于示波器观察）
void test_zeros(void) {
    for (uint8_t i = 0; i < 32; i++) {
        send_bit(0);
    }
    RB1 = 0;
    _delay(60);
}

// 发送1010模式（便于观察对比）
void test_pattern_1010(void) {
    for (uint8_t i = 0; i < 16; i++) {
        send_bit(1);
        send_bit(0);
    }
    RB1 = 0;
    _delay(60);
}

// 测试纯绿色（0xFF0000 - GRB格式）
void test_pure_green(void) {
    ws2812_send_byte(0xFF);  // G
    ws2812_send_byte(0x00);  // R
    ws2812_send_byte(0x00);  // B
    ws2812_reset();
}

// 测试纯红色（0x00FF00 - GRB格式）
void test_pure_red(void) {
    ws2812_send_byte(0x00);  // G
    ws2812_send_byte(0xFF);  // R
    ws2812_send_byte(0x00);  // B
    ws2812_reset();
}

// 测试纯蓝色（0x0000FF - GRB格式）
void test_pure_blue(void) {
    ws2812_send_byte(0x00);  // G
    ws2812_send_byte(0x00);  // R
    ws2812_send_byte(0xFF);  // B
    ws2812_reset();
}

// 测试白色（0xFFFFFF - GRB格式）
void test_white(void) {
    ws2812_send_byte(0xFF);  // G
    ws2812_send_byte(0xFF);  // R
    ws2812_send_byte(0xFF);  // B
    ws2812_reset();
}

// 设置时序参数
void set_timing(uint8_t one_h, uint8_t one_l, uint8_t zero_h, uint8_t zero_l) {
    current_timing.one_high = one_h;
    current_timing.one_low = one_l;
    current_timing.zero_high = zero_h;
    current_timing.zero_low = zero_l;
}

// 主测试函数 - 循环测试不同模式
void run_timing_test(void) {
    static uint8_t test_mode = 0;

    switch (test_mode) {
        case 0:
            test_ones();
            break;
        case 1:
            test_zeros();
            break;
        case 2:
            test_pattern_1010();
            break;
        case 3:
            test_pure_green();
            break;
        case 4:
            test_pure_red();
            break;
        case 5:
            test_pure_blue();
            break;
        case 6:
            test_white();
            break;
    }

    test_mode++;
    if (test_mode > 6) {
        test_mode = 0;
    }

    _delay(500);  // 每个模式间隔500ms
}
