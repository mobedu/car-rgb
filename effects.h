#ifndef __EFFECTS_H
#define __EFFECTS_H
#include "config.h"

// 亮度级别: 0-10 (0=关闭, 10=最亮)
#define BRIGHTNESS_LEVELS  10
#define BRIGHTNESS_DEFAULT 10

// 电池动态亮度上限 (由main.c从电池ADC计算并更新)
extern unsigned char max_brightness_limit;

void effects_init(void);
void effects_set_mode(unsigned char mode);   // 1-8
void effects_next_color(void);               // 同模式切颜色(模式1-3)
void effects_update(void);                   // 每循环调用，驱动动画
void effects_brightness_up(void);
void effects_brightness_down(void);
unsigned char effects_get_brightness(void);

// 由main.c持有，effects模块直接操作
extern RGB_t leds[LED_COUNT];
extern unsigned char color_index;  // 0-9: 10种颜色

#endif
