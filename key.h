#ifndef __KEY_H
#define __KEY_H

typedef enum {
    KEY_NONE = 0,
    KEY_SHORT = 1,
    KEY_LONG = 2
} KeyEvent_t;

KeyEvent_t key_scan(void);

#endif