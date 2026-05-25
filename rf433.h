#ifndef __RF433_H
#define __RF433_H

#include "config.h"

// RF433命令码（基于实测CSV数据分析）
// 协议: 同步头12ms低+1.2ms高, 数据位高>500us=1
// 实测用户码: 0xFFFE, 命令码如下（期望值×2）
#define RF_CMD_ON        0x02  // 亮灯 (期望0x01)
#define RF_CMD_OFF       0x06  // 关灯 (期望0x03)
#define RF_CMD_TIME_4H   0x08  // 4小时定时 (期望0x04)
#define RF_CMD_TIME_6H   0x0A  // 6小时定时 (期望0x05)
#define RF_CMD_TIME_8H   0x0C  // 8小时定时 (期望0x06)
#define RF_CMD_DIM_DOWN  0x0E  // 亮度减小 (期望0x07)
#define RF_CMD_DIM_UP    0x12  // 亮度增加 (期望0x09)
#define RF_CMD_MODE_1    0x16  // 1#亮灯模式 (期望0x0B)
#define RF_CMD_MODE_2    0x18  // 2#亮灯模式 (期望0x0C)
#define RF_CMD_MODE_3    0x1A  // 3#亮灯模式 (期望0x0D)
#define RF_CMD_MODE_4    0x1C  // 4#亮灯模式 (期望0x0E)
#define RF_CMD_MODE_5    0x1E  // 5#亮灯模式 (期望0x0F)
#define RF_CMD_MODE_6    0x20  // 6#亮灯模式 (期望0x10)
#define RF_CMD_MODE_7    0x22  // 7#亮灯模式 (期望0x11)
#define RF_CMD_MODE_8    0x24  // 8#亮灯模式 (期望0x12)
#define RF_CMD_TIME_OFF  0x26  // 定时关闭 (期望0x13)
#define RF_CMD_RESET     0x2A  // 复位 (期望0x15)

typedef enum {
    TIMER_OFF,
    TIMER_4H,
    TIMER_6H,
    TIMER_8H
} TimerState_t;

extern volatile unsigned char rf433_received;
extern volatile unsigned char rf433_command;
extern volatile unsigned char rf433_24bit_received;
extern volatile unsigned long isr_count;
extern volatile unsigned char code1, code2, code3;

void rf433_init(void);
void rf433_turn_on(void);
void rf433_turn_off(void);
unsigned char rf433_has_command(void);
unsigned char rf433_get_command(void);
void rf433_clear_command(void);
void rf433_timer_isr(void);

#endif