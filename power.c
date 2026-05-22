#include "power.h"

unsigned char power_state = 0;

void power_off_leds(RGB_t *leds) {
    unsigned char i;
    for (i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}