#include <sc.h>
#include "config.h"
#include "rf433.h"

volatile unsigned char rf433_received = 0;
volatile unsigned char rf433_command = 0;
volatile TimerState_t timer_state = TIMER_OFF;
volatile unsigned int timer_counter = 0;

static volatile unsigned char level_l_num = 0;
static volatile unsigned char level_h_num = 0;
static volatile unsigned char level_last_flag = 0;
static volatile unsigned char rf_syn = 0;
static volatile unsigned char rf_num = 0;
static volatile unsigned char code1 = 0, code2 = 0, code3 = 0;
static volatile unsigned int s = 0;

void rf433_init(void) {
    // RA2 SHUT
    TRISA &= ~(1 << 2);
    ANSEL0 &= ~(1 << 2);
    RA2 = 0;

    // RA3 RF input
    TRISA |= (1 << 3);
    ANSEL1 &= ~(1 << 3);

    // Timer2: Fosc/4, 1:1, 16MHz/4/71 ≈ 18us
    T2CON = 0x01;
    TMR2 = 0;
    PR2 = 70;
    TMR2IF = 0;
    TMR2IE = 1;
    PEIE = 1;

    level_l_num = level_h_num = level_last_flag = 0;
    rf_syn = rf_num = 0;
    code1 = code2 = code3 = 0;
    s = 0;
    rf433_received = 0;
}

void rf433_turn_on(void) { RA2 = 0; }
void rf433_turn_off(void) { RA2 = 1; }
unsigned char rf433_is_on(void) { return (RA2 == 0); }

void rf433_timer_isr(void) {
    TMR2IF = 0;
    TMR2ON = 0;
    TMR2 = 0;
    PR2 = 70;
    TMR2ON = 1;

    if (RA3 == 0) {
        level_l_num++;
        level_last_flag = 0;
        if (level_l_num > 200) {
            level_l_num = 0;
            rf_syn = 0;
        }
    } else {
        level_h_num++;
        if (level_last_flag == 0) {
            if ((level_l_num >= 100) && (level_l_num <= 200)) {
                rf_syn = 1;
                rf_num = 0;
                code1 = code2 = code3 = 0;
            } else if (rf_syn && (level_l_num > 7) && (level_l_num <= 20)) {
                rf_num++;
                if (rf_num > 23) {
                    if (!rf433_received &&
                        (code1 == 0x01 || code1 == 0x03 || code1 == 0x04 ||
                         code1 == 0x05 || code1 == 0x06 || code1 == 0x07 || code1 == 0x09 ||
                         code1 == 0x0B || code1 == 0x0C || code1 == 0x0D || code1 == 0x0E ||
                         code1 == 0x0F || code1 == 0x10 || code1 == 0x11 || code1 == 0x12 ||
                         code1 == 0x13 || code1 == 0x15) &&
                        (code3 == 0xFF)) {
                        rf433_command = code1;
                        rf433_received = 1;
                        s = 5000;
                    }
                    rf_syn = 0;
                    rf_num = 0;
                }
            } else if (rf_syn && (level_l_num >= 1) && (level_l_num <= 6)) {
                switch (rf_num) {
                    case 0:  code1 |= 0x80; break;
                    case 1:  code1 |= 0x40; break;
                    case 2:  code1 |= 0x20; break;
                    case 3:  code1 |= 0x10; break;
                    case 4:  code1 |= 0x08; break;
                    case 5:  code1 |= 0x04; break;
                    case 6:  code1 |= 0x02; break;
                    case 7:  code1 |= 0x01; break;
                    case 8:  code2 |= 0x80; break;
                    case 9:  code2 |= 0x40; break;
                    case 10: code2 |= 0x20; break;
                    case 11: code2 |= 0x10; break;
                    case 12: code2 |= 0x08; break;
                    case 13: code2 |= 0x04; break;
                    case 14: code2 |= 0x02; break;
                    case 15: code2 |= 0x01; break;
                    case 16: code3 |= 0x80; break;
                    case 17: code3 |= 0x40; break;
                    case 18: code3 |= 0x20; break;
                    case 19: code3 |= 0x10; break;
                    case 20: code3 |= 0x08; break;
                    case 21: code3 |= 0x04; break;
                    case 22: code3 |= 0x02; break;
                    case 23: code3 |= 0x01;
                        if (!rf433_received &&
                            (code1 == 0x01 || code1 == 0x03 || code1 == 0x04 ||
                             code1 == 0x05 || code1 == 0x06 || code1 == 0x07 || code1 == 0x09 ||
                             code1 == 0x0B || code1 == 0x0C || code1 == 0x0D || code1 == 0x0E ||
                             code1 == 0x0F || code1 == 0x10 || code1 == 0x11 || code1 == 0x12 ||
                             code1 == 0x13 || code1 == 0x15) &&
                            (code3 == 0xFF)) {
                            rf433_command = code1;
                            rf433_received = 1;
                            s = 5000;
                        }
                        rf_num = 0;
                        rf_syn = 0;
                    default: rf_num = 0; break;
                }
                rf_num++;
            } else {
                rf_num = 0;
                rf_syn = 0;
                code3 = code2 = code1 = 0;
            }
            level_l_num = 0;
        }
        level_last_flag = 1;
    }

    if (rf433_received) {
        if (s > 0) s--;
        if (s == 0) rf433_received = 0;
    }
}

unsigned char rf433_has_command(void) {
    if (rf433_received) {
        rf433_received = 0;
        return 1;
    }
    return 0;
}

unsigned char rf433_get_command(void) {
    return rf433_command;
}

void rf433_update_timer(void) {
    if (timer_state != TIMER_OFF && timer_counter < 65535) timer_counter++;
}

unsigned char rf433_timer_expired(void) {
    if (timer_state == TIMER_OFF) return 0;
    unsigned int t = (timer_state == TIMER_4H) ? 14400 : (timer_state == TIMER_6H) ? 21600 : 28800;
    if (timer_counter >= t) {
        timer_state = TIMER_OFF;
        timer_counter = 0;
        return 1;
    }
    return 0;
}