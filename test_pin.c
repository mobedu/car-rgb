
#include <sc.h>
#include "config.h"

void main(void) {
    // 1. 关闭所有模拟输入
    ANSEL0 = 0U;
    ANSEL1 = 0U;

    // 2. 设置 RB1 为输出
    TRISB &= (uint8_t)~(1U << 1);

    // 3. 循环翻转 RB1
    while (1) {
        PORTB |= (1U << 1);    // 拉高
        __delay_ms(500);
        PORTB &= (uint8_t)~(1U << 1);  // 拉低
        __delay_ms(500);
    }
}
