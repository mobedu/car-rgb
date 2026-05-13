// 时钟频率测试程序
// 用示波器测量RB1引脚，计算实际系统频率
//
// 预期：如果16MHz且4T模式，10个NOP = 2.5us
// 如果测量结果是20us，说明时钟是2MHz
// 如果测量结果是40us，说明时钟是1MHz

#include <sc.h>
#include "config.h"

extern void ws2812_init(void);

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
    OSCCON = 0x70;  // 16MHz内部振荡 (IRCF<2:0>=111)

    ws2812_init();

    // GPIO翻转测试 - 用示波器测量周期
    while(1) {
        RB1 = 1;
        // 10个NOP + 指令开销
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        RB1 = 0;
        // 10个NOP + 指令开销
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
        asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    }

    // 计算公式：
    // 实测周期T(us) → 频率F = 20/T (MHz)
    // 例如：T=2.5us → F=8MHz (4T模式)
    //      T=5us   → F=4MHz
    //      T=10us  → F=2MHz
    //      T=20us  → F=1MHz
}
