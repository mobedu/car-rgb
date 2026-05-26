#ifndef __POWER_H
#define __POWER_H

#include <sc.h>
#include "config.h"

extern unsigned char power_state;

void power_off_leds(RGB_t *leds);

#endif