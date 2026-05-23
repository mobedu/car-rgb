#ifndef __EFFECTS_NEW_H
#define __EFFECTS_NEW_H
extern volatile EffectMode_t current_effect;
extern RGB_t leds[LED_COUNT];
extern unsigned char g_color_index;
void effect_new_init(void);
void effect_new_execute(EffectMode_t);
void effects_new_update(void);
#endif