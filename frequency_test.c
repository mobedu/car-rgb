// 系统频率精确测量程序
// 用示波器测量RB1引脚的翻转周期
//
// 计算公式:
// 周期T(us) → 指令频率 = 4/T (MHz)
// 系统频率 = 指令频率 × 4 (MHz)
//
// 预期结果 (OSCCON=0x70):
//   2个NOP + RB1翻转 = 4指令 = 1us @ 4MHz指令率
//   完整周期(高+低) = 2us → 系统频率16MHz ✓

#include <sc.h>
#include "config.h"

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

    // 测试不同的OSCCON配置
    // 先测试0x70 (16MHz预设)
    OSCCON = 0x70;

    // GPIO翻转测试 - 固定2个NOP
    while(1) {
        RB1 = 1;
        asm("nop"); asm("nop");  // 2个NOP
        RB1 = 0;
        asm("nop"); asm("nop");  // 2个NOP
    }

    // 如果测量结果是:
    // 高1us, 低1us (周期2us) → 4MHz指令率 → 16MHz系统频率 ✓
    // 高2us, 低2us (周期4us) → 2MHz指令率 → 8MHz系统频率
    // 高4us, 低4us (周期8us) → 1MHz指令率 → 4MHz系统频率
    // 高8us, 低8us (周期16us) → 500kHz指令率 → 2MHz系统频率
}
