// WS2812 简单时序测试程序
// 使用说明：
// 1. 修改下面的 TIMING_CONFIG 值来调整时序
// 2. 编译并烧录到芯片
// 3. 用示波器/逻辑分析仪观察 RB1 引脚
// 4. 或直接观察LED颜色是否正确

#include <sc.h>
#include "config.h"
#include "ws2812.h"

// ========== 时序配置区域 ==========
// 格式: ONE_HIGH_NOP, ONE_LOW_NOP, ZERO_HIGH_NOP, ZERO_LOW_NOP
// 说明:
//   1码: 高电平 ONE_HIGH_NOP 个NOP, 低电平 ONE_LOW_NOP 个NOP
//   0码: 高电平 ZERO_HIGH_NOP 个NOP, 低电平 ZERO_LOW_NOP 个NOP
//   每个NOP = 125ns (16MHz/2T模式)

// 推荐配置（根据实测调整）:
#define TIMING_CONFIG 6, 2, 2, 6  // 标准配置 - 如果颜色不对，尝试其他配置

// 其他可尝试的配置（取消注释测试）:
// #define TIMING_CONFIG 7, 2, 2, 6  // 1码高电平更长
// #define TIMING_CONFIG 6, 3, 2, 6  // 1码低电平更长
// #define TIMING_CONFIG 5, 2, 2, 5  // 短周期
// #define TIMING_CONFIG 7, 2, 3, 7  // 长周期
// #define TIMING_CONFIG 6, 2, 3, 6  // 0码高电平更长
// #define TIMING_CONFIG 6, 2, 2, 7  // 0码低电平更长

// ========== 测试模式选择 ==========
// 选择要测试的模式（取消注释一个）:

#define TEST_MODE COLOR_CYCLE  // 自动循环颜色
// #define TEST_MODE PURE_GREEN  // 纯绿色
// #define TEST_MODE PURE_RED    // 纯红色
// #define TEST_MODE PURE_BLUE   // 纯蓝色
// #define TEST_MODE WHITE       // 白色
// #define TEST_MODE TIMING_TEST // 时序测试（用于示波器）

// ========== 延时配置 ==========
#define CYCLE_DELAY_MS  1000  // 颜色切换间隔(ms)

// ========== 测试函数 ==========

// 发送全1码（用于示波器观察）
void send_test_ones(uint8_t count) {
    while (count--) {
        RB1 = 1;
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        RB1 = 0;
        asm("nop"); asm("nop");
    }
}

// 发送全0码（用于示波器观察）
void send_test_zeros(uint8_t count) {
    while (count--) {
        RB1 = 1;
        asm("nop"); asm("nop");
        RB1 = 0;
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    }
}

// 发送1010模式（用于对比观察）
void send_test_pattern(void) {
    for (uint8_t i = 0; i < 16; i++) {
        RB1 = 1;
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        RB1 = 0;
        asm("nop"); asm("nop");

        RB1 = 1;
        asm("nop"); asm("nop");
        RB1 = 0;
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    }
}

void main(void) {
    // 系统初始化
    ANSEL0 = 0;
    ANSEL1 = 0;
    ODCONA = 0;
    ODCONB = 0;
    WPUB = 0;
    WPUA = 0;
    TRISB = 0xFC;
    PORTB = 0x00;
    PORTA = 0x00;
    TRISA = 0xFF;
    ANS0 = 0;
    OSCCON = 0x40;  // 16MHz内部时钟

    ws2812_init();

    // 应用时序配置
    ws2812_set_timing(TIMING_CONFIG);

    // 主测试循环
    while (1) {
#if (TEST_MODE == COLOR_CYCLE)
        // 颜色循环测试
        ws2812_set_all(0, 255, 0);   // 绿色
        _delay(CYCLE_DELAY_MS);

        ws2812_set_all(255, 0, 0);   // 红色
        _delay(CYCLE_DELAY_MS);

        ws2812_set_all(0, 0, 255);   // 蓝色
        _delay(CYCLE_DELAY_MS);

        ws2812_set_all(255, 255, 255); // 白色
        _delay(CYCLE_DELAY_MS);

#elif (TEST_MODE == PURE_GREEN)
        ws2812_set_all(0, 255, 0);  // 纯绿
        _delay(500);

#elif (TEST_MODE == PURE_RED)
        ws2812_set_all(255, 0, 0);  // 纯红
        _delay(500);

#elif (TEST_MODE == PURE_BLUE)
        ws2812_set_all(0, 0, 255);  // 纯蓝
        _delay(500);

#elif (TEST_MODE == WHITE)
        ws2812_set_all(255, 255, 255);  // 白色
        _delay(500);

#elif (TEST_MODE == TIMING_TEST)
        // 时序测试 - 用示波器观察
        send_test_ones(32);
        _delay(500);
        send_test_zeros(32);
        _delay(500);
        send_test_pattern();
        _delay(500);

#endif
    }
}
