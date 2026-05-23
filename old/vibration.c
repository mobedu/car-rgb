#include <sc.h>
#include "config.h"

volatile unsigned char vibration_wakeup = 0;
static unsigned char vibration_last = 1;

void vibration_init(void) {
    ANSEL0 &= ~(1 << 1);
    TRISA |= (1 << 1);
    vibration_last = 1;
    vibration_wakeup = 0;
}

unsigned char vibration_detected(void) {
    unsigned char s = vibration_wakeup;
    vibration_wakeup = 0;
    return s;
}

void vibration_check(void) {
    unsigned char current = RA1;
    if (vibration_last == 1 && current == 0) {
        vibration_wakeup = 1;
    }
    vibration_last = current;
}