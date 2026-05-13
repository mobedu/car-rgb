#ifndef __CONFIG_H
#define __CONFIG_H

#include <stdint.h>

#define USE_16MHZ          1
#if USE_16MHZ
#define _XTAL_FREQ         16000000UL
#else
#define _XTAL_FREQ         4000000UL
#endif
#define LED_COUNT          24

typedef enum {
    EFFECT_BREATH = 0,    // ɫ
    EFFECT_TWINKLE,       // 
    EFFECT_CHASE,         // ׷
    EFFECT_EXPAND,        // ɢ
    EFFECT_MARQUEE,       // 
    EFFECT_STACK,         // 
    EFFECT_POLICE,

    EFFECT_COUNT
} EffectMode_t;

// RGB ɫṹ
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB_t;

// Чӿ
typedef struct {
    void (*init)(void);
    void (*update)(void);
} Effect_t;

extern volatile uint16_t system_tick_ms;
extern volatile EffectMode_t current_effect;
extern RGB_t leds[LED_COUNT];

#endif
