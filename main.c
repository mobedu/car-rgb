#include <sc.h>
#include "effects.h"
#include "ws2812.h"

// ========== Configuration ==========
#define LED_NUM         24       // LED count (���ݾɴ���)

// ========== System Clock Initialization ==========
void system_clock_init(void) {
    // ����ϵͳʱ��Ϊ 16MHz
    // IRCF<2:0>=111 (16MHz), SWDTEN=0
    OSCCON = 0x70;

    // ����ʱ��ӷƵ�� CLKDIV<2:0>=010 (1/4���)��16MHz/4 = 4MHz
    // ��4MHz���ִ��4Tģʽ��ʵ��1MHzָ��ٶ���
    // ��16MHz��� 2T ģʽ��8MHzָ����
    PWMCON0 = (PWMCON0 & 0x1F) | 0xC0;  // CLKDIV=110 (1/2分频)

    // ��ʱȷ��ʱ���ȶ�
    unsigned char i;
    for (i = 0; i < 20; i++) {
        asm("nop");
    }
}

// ========== Delay Functions ==========
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 1333; j++) {   // 16MHz 2T mode ~1ms
            asm("nop");
        }
    }
}

// ========== WS2812B Driver ==========
// ����һ���ֽڣ�ֱ��λչ��������֧
static void ws2812_send_byte(unsigned char byte) {
    GIE = 0;

    // Bit 7
    if (byte & 0x80) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }
    // Bit 6
    if (byte & 0x40) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }
    // Bit 5
    if (byte & 0x20) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }
    // Bit 4
    if (byte & 0x10) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }
    // Bit 3
    if (byte & 0x08) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }
    // Bit 2
    if (byte & 0x04) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }
    // Bit 1
    if (byte & 0x02) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }
    // Bit 0
    if (byte & 0x01) {
        RB1 = 1; asm("nop"); asm("nop");
        RB1 = 0; asm("nop"); asm("nop");
    } else {
        RB1 = 1; asm("nop");
        RB1 = 0; asm("nop"); asm("nop"); asm("nop");
    }

    GIE = 1;
}

static void ws2812_send_color(RGB_t color) {
    ws2812_send_byte(color.g);
    ws2812_send_byte(color.r);
    ws2812_send_byte(color.b);
}

static void ws2812_reset(void) {
    RB1 = 0;
    delay_ms(1);   // >50us
}

void ws2812_update_RGB(RGB_t *leds, unsigned char num) {
    unsigned char i;
    unsigned char key_was_pressed = 0;

    // ����ǰ��鰴��״̬
    if (RA0 == 0) {
        key_was_pressed = 1;
    }

    GIE = 0;
    for (i = 0; i < num; i++) {
        ws2812_send_color(leds[i]);
    }
    ws2812_reset();
    GIE = 1;

    // ���ͺ����֮ǰ��⵽�������Ұ������ͷţ���������
    if (key_was_pressed && RA0 == 1) {
        EffectMode_t next_mode = (current_effect + 1) % EFFECT_COUNT;
        effect_execute(next_mode);
    }
}

// ========== GPIO Initialization ==========
static void ws2812_gpio_init(void) {
    // ���� RA0 Ϊ���루������
    TRISA |= (1 << 0);    // RA0 ��Ϊ����

    // ANSEL0 ���� bit0������ RA0 ģ�⹦�ܣ�
    ANSEL0 &= ~(1 << 0);

    // ANSEL1 (94H): Bit1 = ANS9 = RB1, set to 0 for digital I/O
    ANSEL1 &= ~(1 << 1);

    // TRISB (05H): Bit1 = TRISB1, set to 0 for output
    TRISB &= ~(1 << 1);

    // RB1 = 0 initial low
    RB1 = 0;
}

// ========== Key Function (RA0, active low) ==========
static unsigned char power_state = 1;  // 1=��, 0=��
static unsigned char key_press_counter = 0;  // ����������
static unsigned char key_pressed = 0;  // �����Ѱ��±�־

void key_scan(void) {
    if (RA0 == 0) {
        // ��������
        if (!key_pressed) {
            delay_ms(20);  // ����
            if (RA0 == 0) {
                key_pressed = 1;
                key_press_counter = 0;
            }
        } else {
            // �����������£�����
            if (key_press_counter < 255) {
                key_press_counter++;
            }
            // ������⣺Լ1.5�루150��10msѭ����
            if (key_press_counter == 150) {
                // �������л�����
                power_state = !power_state;
                if (!power_state) {
                    // �رգ�ȫ��
                    unsigned char i;
                    for (i = 0; i < LED_COUNT; i++) {
                        leds[i].r = 0;
                        leds[i].g = 0;
                        leds[i].b = 0;
                    }
                    ws2812_update_RGB(leds, LED_COUNT);
                }
                // �ȴ������ͷ�
                while (RA0 == 0);
                key_pressed = 0;
                key_press_counter = 0;
            }
        }
    } else {
        // �����ͷ�
        if (key_pressed) {
            if (key_press_counter < 150) {
                // �̰����л�Ч��
                if (power_state) {
                    EffectMode_t next_mode = (current_effect + 1) % EFFECT_COUNT;
                    effect_execute(next_mode);
                }
            }
            key_pressed = 0;
            key_press_counter = 0;
        }
    }
}

// ========== Function Declarations ==========
extern void effect_init(void);
extern void effect_execute(EffectMode_t mode);
extern RGB_t leds[LED_COUNT];

// ========== Main Function ==========
void main(void) {
    // ������������ϵͳʱ�ӵ� 16MHz
    system_clock_init();

    // WPUA (88H): Bit0 = WPUA0, set to 1 for pull-up
    WPUA |= (1 << 0);

    // Initialize GPIO for WS2812
    ws2812_gpio_init();

    // ��ʼ��Ч��
    effect_init();

    // ��ѭ��
    unsigned int update_counter = 0;
    while (1) {
        // ɨ�谴��
        key_scan();

        // ����Ч����ÿ 10ms��
        update_counter++;
        if (update_counter >= 10) {
            update_counter = 0;

            // ֻ���ڿ���״̬�²Ÿ���Ч��
            if (power_state) {
                // ���õ�ǰЧ���ĸ��º���
                effects_update();
            }

            // �������ݵ� LED
            ws2812_update_RGB(leds, LED_COUNT);
        }

        // ������ʱ���������ռ�� CPU
        delay_ms(1);
    }
}
