#include "power.h"

// 注意：power_state 在 main.c 中定义，这里只使用 extern 声明

void power_off_leds(RGB_t *leds) {
    unsigned char i;
    for (i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}