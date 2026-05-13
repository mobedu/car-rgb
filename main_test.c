#include "SC8F072.h"

// 简单测试：用软件延时驱动WS2812B
void delay_ns(unsigned int n) {
    while(n--);
}

void send_bit(unsigned char bit_val) {
    if (bit_val) {
        // 发送1：高700ns，低800ns
        RB1 = 1;
        delay_ns(3);  // 700ns
        RB1 = 0;
        delay_ns(4);  // 800ns
    } else {
        // 发送0：高350ns，低800ns
        RB1 = 1;
        delay_ns(2);  // 350ns
        RB1 = 0;
        delay_ns(4);  // 800ns
    }
}

void main(void) {
    // 初始化
    ANSEL1 &= ~(1 << 1);
    TRISB1 = 0;
    RB1 = 0;
    
    // 测试：发送一个红色LED
    unsigned char i;
    for(i = 0; i < 8; i++) send_bit(0);  // G=0
    for(i = 0; i < 8; i++) send_bit(1);  // R=255
    for(i = 0; i < 8; i++) send_bit(0);  // B=0
    
    // 复位
    RB1 = 0;
    delay_ns(2000);  // 50μs
    
    while(1);
}
