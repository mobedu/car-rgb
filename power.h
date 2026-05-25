#ifndef __POWER_H
#define __POWER_H

#include <sc.h>
#include "config.h"

extern unsigned char power_state;
extern unsigned char solar_auto_enabled;  // 太阳能自动控制: 1=允许开灯, 0=环境亮禁止开灯

void power_off_leds(RGB_t *leds);

// ADC functions
void adc_init(void);
unsigned int battery_read_adc(void);
unsigned int solar_read_adc(void);
unsigned char get_battery_brightness(unsigned int bat_adc);
void solar_auto_control(void);

#endif