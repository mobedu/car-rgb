#ifndef __RF433_H
#define __RF433_H

#include "config.h"

// RF433命令码（按PIN.md）
#define RF_CMD_ON        0x01  // 亮灯
#define RF_CMD_OFF       0x03  // 关灯
#define RF_CMD_TIME_4H   0x04  // 4小时定时
#define RF_CMD_TIME_6H   0x05  // 6小时定时
#define RF_CMD_TIME_8H   0x06  // 8小时定时
#define RF_CMD_DIM_DOWN  0x07  // 亮度减小
#define RF_CMD_DIM_UP    0x09  // 亮度增加
#define RF_CMD_MODE_1    0x0B  // 1#亮灯模式
#define RF_CMD_MODE_2    0x0C  // 2#亮灯模式
#define RF_CMD_MODE_3    0x0D  // 3#亮灯模式
#define RF_CMD_MODE_4    0x0E  // 4#亮灯模式
#define RF_CMD_MODE_5    0x0F  // 5#亮灯模式
#define RF_CMD_MODE_6    0x10  // 6#亮灯模式
#define RF_CMD_MODE_7    0x11  // 7#亮灯模式
#define RF_CMD_MODE_8    0x12  // 8#亮灯模式
#define RF_CMD_TIME_OFF  0x13  // 定时关闭
#define RF_CMD_RESET     0x15  // 复位

typedef enum {
    TIMER_OFF,
    TIMER_4H,
    TIMER_6H,
    TIMER_8H
} TimerState_t;

extern volatile unsigned char rf433_received;
extern volatile unsigned char rf433_command;
extern volatile unsigned char rf433_24bit_received;  // 调试：24位已接收
extern volatile unsigned long isr_count;  // 调试用
extern volatile unsigned char code1, code2, code3;  // 调试：解码后的24位数据

void rf433_init(void);
void rf433_turn_on(void);
void rf433_turn_off(void);
unsigned char rf433_has_command(void);
unsigned char rf433_get_command(void);
void rf433_clear_command(void);
void rf433_timer_isr(void);

#endif