#include "ws2812.h"
#include "config.h"

volatile unsigned char __ws_dly;

// WS2812 timing (16MHz)
#define S0  PORTB |= (1 << PIN_WS2812B_BIT); __ws_dly = 0; __ws_dly = 0; PORTB &= ~(1 << PIN_WS2812B_BIT)
#define S1  PORTB |= (1 << PIN_WS2812B_BIT); __ws_dly = 0; __ws_dly = 0; __ws_dly = 0; __ws_dly = 0; __ws_dly = 0; PORTB &= ~(1 << PIN_WS2812B_BIT)

static void send_byte(unsigned char b) {
    if (b & 0x80) { S1; } else { S0; }
    if (b & 0x40) { S1; } else { S0; }
    if (b & 0x20) { S1; } else { S0; }
    if (b & 0x10) { S1; } else { S0; }
    if (b & 0x08) { S1; } else { S0; }
    if (b & 0x04) { S1; } else { S0; }
    if (b & 0x02) { S1; } else { S0; }
    if (b & 0x01) { S1; } else { S0; }
    __ws_dly = 0;
}

void ws2812_update(RGB_t *leds, unsigned char n) {
    unsigned char i;
    INTCON &= ~(1 << 7);  // GIE = 0
    for (i = 0; i < n; i++) {
        send_byte(leds[i].g);
        send_byte(leds[i].r);
        send_byte(leds[i].b);
    }
    PORTB &= ~(1 << PIN_WS2812B_BIT);
    for (i = 0; i < 200; i++) __ws_dly = 0;
    INTCON |= (1 << 7);   // GIE = 1
}