#include "timer.h"

volatile unsigned int timer_ticks = 0;       // Increments every ~16.4ms
volatile unsigned int timer_seconds = 0;      // Increments every ~1 second
volatile unsigned char timer_triggered = 0;   // Set each second

// Timer0: 1:256 prescaler, Fosc/4 internal clock
// At 16MHz: TMR0 increments every 0.25µs
// 256 counts × 0.25µs × 256 prescaler = 16.384ms per overflow
#define TIMER0_OVERFLOWS_PER_SEC 122  // ~1 second (实测补偿2x)

void timer0_init(void) {
    TMR0 = TIMER0_RELOAD_VALUE;
    timer_ticks = 0;
    timer_seconds = 0;
    timer_triggered = 0;

    // OPTION_REG configuration:
    // Bit7 T0LSE_EN=0: T0CS source
    // Bit6 T0CS=0: Internal clock (Fosc/4)
    // Bit5 T0SE=0: Not used for timer
    // Bit4 PSA=0: Prescaler assigned to Timer0
    // Bits3-0 PS2-PS0=111: 1:256 prescaler
    OPTION_REG = 0x07;  // 0000 0111
}

void timer0_tick(void) {
    TMR0 = TIMER0_RELOAD_VALUE;

    timer_ticks++;
    if (timer_ticks >= TIMER0_OVERFLOWS_PER_SEC) {
        timer_ticks = 0;
        timer_seconds++;
        timer_triggered = 1;
    }
}