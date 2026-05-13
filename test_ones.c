// 极简测试2: 只发送1码
// 发送 0xFF, 0xFF, 0xFF (24个1码)
// 预期: LED亮白色 (最亮)
// 对比test_zeros.c来验证0码和1码都能区分

#include <sc.h>
#include "config.h"

void main(void) {
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
    OSCCON = 0x70;  // 16MHz

    // 初始化WS2812引脚
    ANSEL1 &= ~(1 << 1);
    TRISB1 = 0;
    RB1 = 0;

    // 发送24个1码 (0xFF, 0xFF, 0xFF)
    // 1码: RB1=1, 3 NOP, RB1=0
    asm volatile (
        ".rept 24 \n\t"
        "bsf _PORTB, 1 \n\t"     // RB1 = 1
        "nop \n\t"
        "nop \n\t"
        "nop \n\t"
        "bcf _PORTB, 1 \n\t"     // RB1 = 0
        ".endr \n\t"
    );

    // 复位信号
    asm volatile (
        ".rept 250 \n\t"
        "nop \n\t"
        ".endr \n\t"
    );

    while(1) {
        // 每秒重新发送
        asm volatile (
            ".rept 24 \n\t"
            "bsf _PORTB, 1 \n\t"
            "nop \n\t"
            "nop \n\t"
            "nop \n\t"
            "bcf _PORTB, 1 \n\t"
            ".endr \n\t"
        );
        asm volatile (
            ".rept 250 \n\t"
            "nop \n\t"
            ".endr \n\t"
        );
    }
}
