#ifndef __RF433_H
#define __RF433_H
#include <sc.h>

#define RF433_CMD_OFF       0x03
#define RF433_CMD_ON        0x01
#define RF433_CMD_TIME_4H   0x04
#define RF433_CMD_TIME_6H   0x05
#define RF433_CMD_TIME_8H   0x06
#define RF433_CMD_DIM_DOWN  0x07
#define RF433_CMD_DIM_UP    0x09
#define RF433_CMD_MODE_1    0x0B
#define RF433_CMD_MODE_2    0x0C
#define RF433_CMD_MODE_3    0x0D
#define RF433_CMD_MODE_4    0x0E
#define RF433_CMD_MODE_5    0x0F
#define RF433_CMD_MODE_6    0x10
#define RF433_CMD_MODE_7    0x11
#define RF433_CMD_MODE_8    0x12
#define RF433_CMD_TIME_OFF  0x13
#define RF433_CMD_RESET     0x15

typedef enum { TIMER_OFF, TIMER_4H, TIMER_6H, TIMER_8H } TimerState_t;

extern volatile unsigned char rf433_received;
extern volatile unsigned char rf433_command;
extern volatile TimerState_t timer_state;
extern volatile unsigned int timer_counter;

void rf433_init(void);
void rf433_turn_on(void);
void rf433_turn_off(void);
unsigned char rf433_is_on(void);
unsigned char rf433_has_command(void);
unsigned char rf433_get_command(void);
void rf433_update_timer(void);
unsigned char rf433_timer_expired(void);
void rf433_timer_isr(void);
#endif