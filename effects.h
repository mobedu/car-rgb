#ifndef __EFFECTS_H
#define __EFFECTS_H
#include "config.h"

void effects_init(void);
void effects_next_color(void);
void effects_apply(RGB_t *leds);
#endif
