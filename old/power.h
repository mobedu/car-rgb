#ifndef __POWER_H
typedef enum { POWER_STATE_ACTIVE, POWER_STATE_SLEEP_AUTO } PowerState_t;
typedef enum { SLEEP_MODE_SLEEP } SleepMode_t;
typedef enum {
    WAKEUP_SOURCE_NONE, WAKEUP_SOURCE_KEY, WAKEUP_SOURCE_RF433, WAKEUP_SOURCE_VIBRATION
} WakeupSource_t;

extern volatile PowerState_t system_power_state;
extern volatile unsigned char idle_counter;

void power_manager_init(void);
void power_enter_sleep(SleepMode_t);
void power_wakeup_handler(WakeupSource_t);
void power_update_idle_counter(void);
void power_reset_idle_counter(void);
PowerState_t power_get_state(void);
#endif