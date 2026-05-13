#ifndef __WS2812_H
#define __WS2812_H

#include <sc.h>
#include "config.h"

void ws2812_update_RGB(RGB_t *leds, unsigned char num);

#endif
