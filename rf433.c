#include <sc.h>
#include "rf433.h"
#include "config.h"

volatile unsigned char rf433_received = 0;
volatile unsigned char rf433_command = 0;
volatile unsigned char rf433_24bit_received = 0;
volatile unsigned char code1 = 0, code2 = 0, code3 = 0;
volatile unsigned int rf433_debug = 0;

static volatile unsigned char rf_syn = 0;
static volatile unsigned char rf_num = 0;
static volatile unsigned int s = 0;
volatile unsigned long isr_count = 0;

static volatile unsigned int low_width = 0;
static volatile unsigned int high_width = 0;
static volatile unsigned int prev_high = 0;  // 保存上一个HIGH宽度用于bit解码
static volatile unsigned char high_captured = 0;  // 标记第一个bit的HIGH是否已捕获
static volatile unsigned char last_level = 0;

// RF433解码参数（1527协议，基于19.csv逻辑分析仪实测）
// 同步: >10ms低电平 标记帧开始 (实测~12-14ms)
// EOB: >37ms低电平标记按键释放 (实测~38ms)
// 数据: 24bit PWM (1527标准), 每bit = HIGH + LOW, 周期~1.6ms
// Bit 1: HIGH~1.2ms(67 ticks) + LOW~0.4ms(22 ticks), HIGH > LOW
// Bit 0: HIGH~0.4ms(22 ticks) + LOW~1.2ms(67 ticks), HIGH < LOW
// Timer2周期 = 18us
#define SYNC_MIN         550   // ~10ms / 18us (实测最小675=12ms, 550留余量)
#define EOB_MIN          2000  // ~36ms / 18us (实测最小2147=38ms, 2000防误判)
#define BIT_COUNT        24
#define BIT_MIN_WIDTH    10    // 180us, 过滤噪声毛刺 (实测数据位最小21 ticks=378us)

void rf433_init(void) {
    TRISB &= ~(1 << PIN_SHUT_BIT);
    ANSEL1 &= ~(1 << PIN_SHUT_BIT);
    PORTB &= ~(1 << PIN_SHUT_BIT);

    TRISA |= (1 << PIN_RF_DATA_BIT);
    ANSEL0 &= ~(1 << PIN_RF_DATA_BIT);

    TMR2IF = 0;
    TMR2IE = 1;
    INTCON |= (1 << 6);
    T2CON = 0x05;
    TMR2 = 0;
    PR2 = 70;

    low_width = high_width = 0;
    last_level = 0;
    rf_syn = rf_num = 0;
    code1 = code2 = code3 = 0;
    s = 0;
    rf433_received = 0;
    high_captured = 0;
}

void rf433_turn_on(void) { PORTB &= ~(1 << PIN_SHUT_BIT); }
void rf433_turn_off(void) { PORTB |= (1 << PIN_SHUT_BIT); }

unsigned char rf433_has_command(void) {
    if (rf433_received) { rf433_received = 0; return 1; }
    return 0;
}
unsigned char rf433_get_command(void) { return rf433_command; }
void rf433_clear_command(void) { rf433_command = 0; }

void rf433_timer_isr(void) {
    unsigned char rf_level;
    unsigned char data_bit;
    unsigned char byte_idx;
    unsigned char bit_pos;

    TMR2IF = 0;
    TMR2ON = 0;
    TMR2 = 0;
    PR2 = 70;
    TMR2ON = 1;
    isr_count++;

    rf_level = (PORTA >> PIN_RF_DATA_BIT) & 1;

    if (rf_level == last_level) {
        if (rf_level == 0) {
            low_width++;
        } else {
            high_width++;
        }
    } else {
        // 边沿变化
        if (rf_level == 1) {
            // 上升沿：低电平结束
            if (low_width >= SYNC_MIN) {
                if (low_width >= EOB_MIN) {
                    // EOB (>36ms低电平): 按键发射结束，确认命令
                    if (rf_syn == 2 && !rf433_received && rf433_command != 0) {
                        rf433_received = 1;
                        s = 5000;
                    }
                    rf_syn = 0;
                    rf_num = 0;
                } else if (rf_syn != 1) {
                    // 常规同步头 (10-36ms低电平)，仅在非接收状态时开始新帧
                    rf_syn = 1;
                    rf_num = 0;
                    code1 = code2 = code3 = 0;
                    prev_high = 0;  // 需要特殊处理第一个bit
                }
                // rf_syn==1时忽略同步头(噪声防护)
            }
            else if (rf_syn == 1 && rf_num < BIT_COUNT) {
                // 数据位解码: 比较上一个HIGH和当前LOW
                if (high_captured && prev_high >= BIT_MIN_WIDTH && low_width >= BIT_MIN_WIDTH) {
                    if (prev_high > low_width) {
                        data_bit = 1;
                    } else {
                        data_bit = 0;
                    }
                    if (data_bit) {
                        byte_idx = rf_num / 8;
                        bit_pos = 7 - (rf_num % 8);
                        if (byte_idx == 0) code1 |= (1 << bit_pos);
                        else if (byte_idx == 1) code2 |= (1 << bit_pos);
                        else if (byte_idx == 2) code3 |= (1 << bit_pos);
                    }
                    rf_num++;
                    high_captured = 0;  // 清除标记，准备下一个bit
                }
                // 检查是否完成24位
                if (rf_num >= BIT_COUNT) {
                    rf433_24bit_received = 1;
                    rf433_debug = (code1 << 8) | code2;
                    if (code1 == 0xFF && code2 == 0xFF &&
                        (code3 == 0x01 || code3 == 0x03 || code3 == 0x04 ||
                         code3 == 0x05 || code3 == 0x06 || code3 == 0x07 || code3 == 0x09 ||
                         code3 == 0x0B || code3 == 0x0C || code3 == 0x0D || code3 == 0x0E ||
                         code3 == 0x0F || code3 == 0x10 || code3 == 0x11 || code3 == 0x12 ||
                         code3 == 0x13 || code3 == 0x15)) {
                        rf433_command = code3;
                        rf_syn = 2;  // 仅用户遥控器推进状态，等待EOB
                    }
                    rf_num = 0;
                }
            }
            high_width = 0;
        } else {
            // 下降沿：高电平结束，保存HIGH宽度供下次上升沿比较
            if (rf_syn == 1 && rf_num < BIT_COUNT) {
                prev_high = high_width;
                high_captured = 1;  // 标记HIGH已捕获
            }
            low_width = 0;
        }
        last_level = rf_level;
    }

    if (rf433_received) { if (s > 0) s--; if (s == 0) rf433_received = 0; }
}