#include <sc.h>
#include "iservices.h"
#include "rf433.h"
#include "vibration.h"
#include "power.h"

void timer2_isr(void) {
    if (TMR2IF) {
        TMR2IF = 0;
        rf433_timer_isr();
    }
}

void interrupt ISR(void) {
    asm("clrwdt");
    if (TMR2IF) timer2_isr();
}