// WS2812 诊断程序 - 用于定位白光问题的根本原因
//
// 诊断步骤：
// 1. 测试GPIO能否正常翻转（闪烁测试）
// 2. 测试纯0和纯1数据
// 3. 测试单个颜色分量

#include <sc.h>
#include "config.h"

extern void ws2812_init(void);
extern void ws2812_send_byte(uint8_t data);
extern void ws2812_reset(void);

// 直接GPIO测试 - 验证引脚是否正常工作
void gpio_blink_test(void) {
    // 快速闪烁 - 如果能看到闪烁说明GPIO正常
    for(int i = 0; i < 10; i++) {
        RB1 = 1;
        _delay(100);
        RB1 = 0;
        _delay(100);
    }
}

// 发送全0数据 - 应该LED熄灭（黑色）
void test_all_zeros(void) {
    ws2812_send_byte(0x00);  // G = 0
    ws2812_send_byte(0x00);  // R = 0
    ws2812_send_byte(0x00);  // B = 0
    ws2812_reset();
}

// 发送全1数据 - 应该LED显示白色
void test_all_ones(void) {
    ws2812_send_byte(0xFF);  // G = 255
    ws2812_send_byte(0xFF);  // R = 255
    ws2812_send_byte(0xFF);  // B = 255
    ws2812_reset();
}

// 测试只有绿色分量
void test_green_only(void) {
    // GRB格式: G=255, R=0, B=0
    ws2812_send_byte(0xFF);  // G: 全1
    ws2812_send_byte(0x00);  // R: 全0
    ws2812_send_byte(0x00);  // B: 全0
    ws2812_reset();
}

// 测试只有红色分量
void test_red_only(void) {
    // GRB格式: G=0, R=255, B=0
    ws2812_send_byte(0x00);  // G: 全0
    ws2812_send_byte(0xFF);  // R: 全1
    ws2812_send_byte(0x00);  // B: 全0
    ws2812_reset();
}

// 测试只有蓝色分量
void test_blue_only(void) {
    // GRB格式: G=0, R=0, B=255
    ws2812_send_byte(0x00);  // G: 全0
    ws2812_send_byte(0x00);  // R: 全0
    ws2812_send_byte(0xFF);  // B: 全1
    ws2812_reset();
}

// 测试交替模式 - 验证0码和1码都能正确识别
void test_alternating(void) {
    // GRB格式: G=0xAA(10101010), R=0x55(01010101), B=0x00
    ws2812_send_byte(0xAA);  // G: 10101010
    ws2812_send_byte(0x55);  // R: 01010101
    ws2812_send_byte(0x00);  // B: 00000000
    ws2812_reset();
}

// 手动发送已知时序 - 用于调试
void manual_timing_test(void) {
    // 发送一个字节的0x00 (8个0码)
    for(uint8_t i = 0; i < 8; i++) {
        // 0码: 高375ns + 低1000ns
        RB1 = 1;
        asm("nop"); asm("nop"); asm("nop");
        RB1 = 0;
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    }

    // 发送一个字节的0xFF (8个1码)
    for(uint8_t i = 0; i < 8; i++) {
        // 1码: 高750ns + 低375ns
        RB1 = 1;
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        RB1 = 0;
        asm("nop"); asm("nop"); asm("nop");
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
    OSCCON = 0x40;

    ws2812_init();

    // 诊断测试循环
    while(1) {
        // 步骤1: GPIO翻转测试（快速闪烁）
        // 如果能看到闪烁，说明GPIO和延时工作正常
        gpio_blink_test();
        _delay(2000);

        // 步骤2: 全0测试（应该熄灭）
        test_all_zeros();
        _delay(2000);

        // 步骤3: 全1测试（应该白色）
        test_all_ones();
        _delay(2000);

        // 步骤4: 纯绿测试（应该绿色）
        test_green_only();
        _delay(2000);

        // 步骤5: 纯红测试（应该红色）
        test_red_only();
        _delay(2000);

        // 步骤6: 纯蓝测试（应该蓝色）
        test_blue_only();
        _delay(2000);

        // 步骤7: 交替模式测试
        test_alternating();
        _delay(2000);
    }
}
