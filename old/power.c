#include <sc.h>
#include "config.h"
#include "power.h"
#include "vibration.h"
#include "rf433.h"
#include "ws2812.h"
#include "effects_new.h"
#include "battery.h"

volatile PowerState_t system_power_state = POWER_STATE_ACTIVE;
volatile unsigned char idle_counter = 0;

void power_manager_init(void) {
    system_power_state = POWER_STATE_ACTIVE;
    idle_counter = 0;
    vibration_init();
    rf433_init();
}

void power_enter_sleep(SleepMode_t mode) {
    unsigned char i;
    TMR2IE = PEIE = 1;

    if (mode == SLEEP_MODE_SLEEP) {
        for (i = 0; i < LED_COUNT; i++) leds[i].r = leds[i].g = leds[i].b = 0;
        ws2812_update_RGB(leds, LED_COUNT);
    }

    OSCCON = 0x02;
    asm("nop"); asm("nop");
    asm("sleep");
}

void power_wakeup_handler(WakeupSource_t source) {
    OSCCON = 0x70;
    asm("nop"); asm("nop");
    idle_counter = 0;

    if (source == WAKEUP_SOURCE_KEY || source == WAKEUP_SOURCE_RF433 || source == WAKEUP_SOURCE_VIBRATION) {
        system_power_state = POWER_STATE_ACTIVE;
        battery_clear_protect();
    }
}

void power_update_idle_counter(void) {
    if (idle_counter < 255) idle_counter++;
    if (idle_counter >= 30) {
        idle_counter = 0;
        if (system_power_state == POWER_STATE_ACTIVE) {
            system_power_state = POWER_STATE_SLEEP_AUTO;
        }
    }
}

void power_reset_idle_counter(void) { idle_counter = 0; }
PowerState_t power_get_state(void) { return system_power_state; }