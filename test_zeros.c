// 极简测试1: 只发送0码
// 发送 0x00, 0x00, 0x00 (24个0码)
// 预期: LED熄灭 (全黑)
// 如果还是白色 → 数据未正确接收

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

    // 发送24个0码 (0x00, 0x00, 0x00)
    // 0码: RB1=1, 2 NOP, RB1=0
    asm volatile (
        ".rept 24 \n\t"
        "bsf _PORTB, 1 \n\t"     // RB1 = 1
        "nop \n\t"
        "nop \n\t"
        "bcf _PORTB, 1 \n\t"     // RB1 = 0
        ".endr \n\t"
    );

    // 复位信号 (保持低电平>50us)
    asm volatile (
        ".rept 250 \n\t"
        "nop \n\t"
        ".endr \n\t"
    );

    while(1) {
        // 每秒重新发送一次
        asm volatile (
            ".rept 24 \n\t"
            "bsf _PORTB, 1 \n\t"
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
