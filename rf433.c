#include <sc.h>
#include "rf433.h"
#include "config.h"
#include "ws2812.h"

volatile unsigned char rf433_received = 0;
volatile unsigned char rf433_command = 0;
volatile unsigned char rf433_24bit_received = 0;
volatile unsigned char code1 = 0, code2 = 0, code3 = 0;
volatile unsigned int rf433_debug = 0;

// RF调试变量 - 用于LED状态反馈
volatile unsigned char rf_debug_sync = 0;   // 同步头计数
volatile unsigned char rf_debug_bits = 0;    // 收到的bit数
volatile unsigned char rf_debug_state = 0;    // 0=idle, 1=syncok, 2=receiving, 3=done, 4=cmd_valid

static volatile unsigned char rf_syn = 0;  // 0=idle, 1=synced, 2=receiving
static volatile unsigned char rf_num = 0;
static volatile unsigned int s = 0;
static volatile unsigned int rf_timeout = 0;  // 接收超时计数器
volatile unsigned long isr_count = 0;

// 接收超时 (~500ms)
#define RF_RX_TIMEOUT    25000  // 18us * 25000 ≈ 450ms

static volatile unsigned int low_width = 0;
static volatile unsigned int high_width = 0;
static volatile unsigned char last_level = 0;

// ============================================================
// RF433解码参数（基于实测CSV数据分析）
// ============================================================
// Timer2周期: 18us (PR2=70, T2CON=0x04, T2CKPS=1:1)
//
// 同步头: 低约12ms + 高约1.2ms
//   检测: 低>3ms 且 高在0.8~1.5ms区间
//
// 数据位: 每bit = 低约0.4ms + 高(约0.4ms→0, 约1.2ms→1)
//   高>500us判1, 否则判0
//
// 用户码: 0xFFFF (实测0xFFFE, 1位容错)
// 命令码: 期望值×2 (PT2262编码特征)

#define SYNC_LOW_MIN     560   // >10ms: 10000/18≈556
#define SYNC_HIGH_MIN    44    // >0.8ms: 800/18≈44
#define SYNC_HIGH_MAX    90    // <1.5ms: 1500/18≈83
#define BIT_THRESHOLD    28    // >500us: 500/18≈28
#define BIT_MIN_WIDTH    10    // 滤除毛刺
#define BIT_COUNT        24

void rf433_init(void) {
    rf_debug_state = 0;
    rf_debug_sync = 0;
    rf_debug_bits = 0;

    TRISB &= ~(1 << PIN_SHUT_BIT);
    ANSEL1 &= ~(1 << PIN_SHUT_BIT);
    PORTB &= ~(1 << PIN_SHUT_BIT);

    TRISA |= (1 << PIN_RF_DATA_BIT);
    ANSEL0 &= ~(1 << PIN_RF_DATA_BIT);

    TMR2IF = 0;
    TMR2IE = 1;
    INTCON |= (1 << 6);
    T2CON = 0x04;  // T2CKPS=00→1:1预分频, PR2=70→周期=71/4MHz≈18us
    TMR2 = 0;
    PR2 = 70;

    low_width = high_width = 0;
    last_level = 0;
    rf_syn = rf_num = 0;
    rf_timeout = 0;
    code1 = code2 = code3 = 0;
    s = 0;
    rf433_received = 0;
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
    PORTB ^= (1 << PIN_DEBUG_BIT);  // 翻转RB3，测量ISR频率
    TMR2IF = 0;
    TMR2ON = 0;
    TMR2 = 0;
    PR2 = 70;
    TMR2ON = 1;
    isr_count++;

    unsigned char rf_level = (PORTA >> PIN_RF_DATA_BIT) & 1;

    if (rf_level == last_level) {
        if (rf_level == 0) {
            low_width++;
        } else {
            high_width++;
        }
    } else {
        // ===== 边沿变化 =====
        if (rf_level == 1) {
            // 上升沿: 低电平时序结束
            if (rf_syn == 0) {
                if (low_width >= SYNC_LOW_MIN) {
                    rf_syn = 1;  // 同步低有效，等待验证高电平
                    rf_timeout = RF_RX_TIMEOUT;
                }
            }
            low_width = 0;
            high_width = 0;
        }
        else {
            // 下降沿: 高电平时序结束
            if (rf_syn == 1) {
                if (high_width >= SYNC_HIGH_MIN && high_width <= SYNC_HIGH_MAX) {
                    rf_syn = 2;   // 同步有效，开始接收数据
                    rf_num = 0;
                    code1 = code2 = code3 = 0;
                    rf_debug_state = 2;  // receiving
                } else {
                    rf_syn = 0;   // 无效同步
                }
            }
            else if (rf_syn == 2) {
                if (high_width >= BIT_MIN_WIDTH) {
                    unsigned char data_bit = (high_width > BIT_THRESHOLD) ? 1 : 0;

                    if (data_bit) {
                        unsigned char byte_idx = rf_num / 8;
                        unsigned char bit_pos = 7 - (rf_num % 8);
                        if (byte_idx == 0)      code1 |= (1 << bit_pos);
                        else if (byte_idx == 1) code2 |= (1 << bit_pos);
                        else if (byte_idx == 2) code3 |= (1 << bit_pos);
                    }
                    rf_num++;

                    if (rf_num >= BIT_COUNT) {
                        rf433_24bit_received = 1;
                        rf_debug_bits = rf_num;
                        rf433_debug = (code1 << 8) | code2;
                        rf_debug_state = 3;  // done

                        if (((code1 & 0xF0) == 0xF0 && code3 >= 0x02 && code3 <= 0x2A) ||
                           (code1 == 0xFE && code3 == 0x54)) {  // 兼容0x54(0x27*2)
                            rf433_command = code3;
                            rf433_received = 1;
                            s = 8000;  // 延长有效期，约140ms
                            rf_debug_state = 4;  // cmd valid
                        }
                        rf_syn = 0;
                        rf_num = 0;
                    }
                }
            }
            high_width = 0;
            low_width = 0;
        }
        last_level = rf_level;
    }

    // 接收标志自动清除
    if (rf433_received) { if (s > 0) s--; if (s == 0) rf433_received = 0; }

    // 接收超时处理
    if (rf_syn != 0 && rf_timeout > 0) {
        rf_timeout--;
        if (rf_timeout == 0) {
            rf_syn = 0;
            rf_num = 0;
            rf_debug_state = 0;  // timeout
        }
    }
}
