#ifndef __TIMER_H__
#define __TIMER_H__

#include <sc.h>

#define TIMER0_RELOAD_VALUE  0  // Start from 0 for simplicity
#define TIMER0_TICKS_PER_SECOND 61  // Approximate: 256 counts × 61 = ~1 second

void timer0_init(void);
void timer0_tick(void);

extern volatile unsigned int timer_ticks;       // Increments every ~16.4ms
extern volatile unsigned int timer_seconds;      // Increments every ~1 second
extern volatile unsigned char timer_triggered;    // Set each second
extern volatile unsigned int no_vibr_timer_ticks;
extern volatile unsigned int no_vibr_timer_seconds;

#endif