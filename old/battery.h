#ifndef __BATTERY_H
#define __BATTERY_H
#include <sc.h>

typedef enum {
    BATTERY_FULL = 0, BATTERY_HIGH, BATTERY_MEDIUM, BATTERY_LOW, BATTERY_PROTECTED
} BatteryStatus_t;

extern unsigned char battery_brightness_limit;
extern unsigned char battery_current_limit;
extern unsigned char battery_fade_counter;
extern unsigned char battery_protected;

void battery_adc_init(void);
unsigned int battery_read_voltage(void);
BatteryStatus_t battery_get_status(void);
void battery_update_brightness_limit(void);
void battery_fade_update(void);
unsigned char battery_check_protection(void);
void battery_clear_protect(void);
#endif