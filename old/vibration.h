#ifndef __VIBRATION_H
#define __VIBRATION_H
#include <sc.h>

extern volatile unsigned char vibration_wakeup;

void vibration_init(void);
unsigned char vibration_detected(void);
void vibration_check(void);
#endif