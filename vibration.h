#ifndef __VIBRATION_H
#define __VIBRATION_H

#include "config.h"

// 震动检测引脚 (使用RB0)
#define PIN_VIBR_BIT     0
#define PIN_VIBR_READ()  ((PORTB >> PIN_VIBR_BIT) & 1)

// 函数声明
void vibration_init(void);
void vibration_check(void);
unsigned char vibration_detected(void);

#endif