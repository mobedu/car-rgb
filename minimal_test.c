// 极简WS2812测试 - 只发送纯绿色
// 目的: 验证数据是否真的在发送，时序是否正确
//
// 【修正后使用4T模式时序】
//
// 如果LED显示绿色 → 时序正确
// 如果LED显示白色 → 0码被识别为1码
// 如果LED不亮 → 引脚或电路问题

#include <sc.h>
#include "config.h"

extern void ws2812_init(void);
extern void ws2812_send_byte(uint8_t data);
extern void ws2812_reset(void);

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

    // 只发送纯绿色: G=255, R=0, B=0
    // 在GRB格式下: 先发送G(255)，再发送R(0)，再发送B(0)
    // 修正后时序: 4T模式，1NOP=250ns
    ws2812_send_byte(0xFF);  // G: 11111111 (8个1码: 高750ns/低500ns)
    ws2812_send_byte(0x00);  // R: 00000000 (8个0码: 高500ns/低1000ns)
    ws2812_send_byte(0x00);  // B: 00000000 (8个0码: 高500ns/低1000ns)
    ws2812_reset();

    // 程序停在这里，保持LED状态
    while(1) {
        // 可选: 每秒重新发送一次，防止LED超时复位
        ws2812_send_byte(0xFF);
        ws2812_send_byte(0x00);
        ws2812_send_byte(0x00);
        ws2812_reset();
        _delay(1000);
    }
}
