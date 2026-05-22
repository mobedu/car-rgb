#include "key.h"
#include "config.h"

typedef enum {
    KEY_STATE_IDLE,
    KEY_STATE_DEBOUNCE,
    KEY_STATE_PRESSED,
    KEY_STATE_WAIT_RELEASE
} KeyState_t;

static KeyState_t key_state = KEY_STATE_IDLE;
static unsigned int press_counter = 0;
static KeyEvent_t pending_event = KEY_NONE;

#define LONG_PRESS_THRESHOLD  150    // 1.5秒 (150次 × 10ms)

KeyEvent_t key_scan(void) {
    KeyEvent_t event = pending_event;
    pending_event = KEY_NONE;

    if (event != KEY_NONE) {
        return event;
    }

    switch (key_state) {
        case KEY_STATE_IDLE:
            if (PIN_KEY_READ() == 0) {
                key_state = KEY_STATE_DEBOUNCE;
                press_counter = 0;
            }
            break;

        case KEY_STATE_DEBOUNCE:
            press_counter++;
            if (PIN_KEY_READ() != 0) {
                key_state = KEY_STATE_IDLE;
            } else if (press_counter >= 3) {
                // 去抖动约30ms
                key_state = KEY_STATE_PRESSED;
                press_counter = 0;
            }
            break;

        case KEY_STATE_PRESSED:
            press_counter++;
            if (PIN_KEY_READ() != 0) {
                if (press_counter < LONG_PRESS_THRESHOLD) {
                    pending_event = KEY_SHORT;
                }
                key_state = KEY_STATE_IDLE;
            } else if (press_counter >= LONG_PRESS_THRESHOLD) {
                pending_event = KEY_LONG;
                key_state = KEY_STATE_WAIT_RELEASE;
            }
            break;

        case KEY_STATE_WAIT_RELEASE:
            if (PIN_KEY_READ() != 0) {
                key_state = KEY_STATE_IDLE;
            }
            break;
    }

    return event;
}