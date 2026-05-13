// 极简测试3: 混合测试 - 纯绿色
// 发送 0xFF, 0x00, 0x00
// 预期: LED显示绿色
//
// 数据结构 (GRB格式):
// G(0xFF) = 11111111 (8个1码)
// R(0x00) = 00000000 (8个0码)
// B(0x00) = 00000000 (8个0码)

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

    ANSEL1 &= ~(1 << 1);
    TRISB1 = 0;
    RB1 = 0;

    while(1) {
        // 绿色: G=255(8个1码), R=0(8个0码), B=0(8个0码)

        // 发送G = 0xFF = 8个1码
        asm volatile (
            ".rept 8 \n\t"
            "bsf _PORTB, 1 \n\t"     // RB1 = 1
            "nop \n\t" "nop \n\t" "nop \n\t"
            "bcf _PORTB, 1 \n\t"     // RB1 = 0
            ".endr \n\t"
        );

        // 发送R = 0x00 = 8个0码
        asm volatile (
            ".rept 8 \n\t"
            "bsf _PORTB, 1 \n\t"
            "nop \n\t" "nop \n\t"
            "bcf _PORTB, 1 \n\t"
            ".endr \n\t"
        );

        // 发送B = 0x00 = 8个0码
        asm volatile (
            ".rept 8 \n\t"
            "bsf _PORTB, 1 \n\t"
            "nop \n\t" "nop \n\t"
            "bcf _PORTB, 1 \n\t"
            ".endr \n\t"
        );

        // 复位信号 (>50us)
        asm volatile (
            ".rept 250 \n\t"
            "nop \n\t"
            ".endr \n\t"
        );

        // 延时约1秒
        asm volatile (
            ".rept 2000 \n\t"
            "nop \n\t"
            ".endr \n\t"
        );
    }
}
