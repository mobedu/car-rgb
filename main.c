#include <sc.h>
#include "effects.h"
#include "ws2812.h"

// ========== Configuration ==========
#define LED_NUM         24       // LED count (兼容旧代码)

// ========== System Clock Initialization ==========
void system_clock_init(void) {
    // 设置系统时钟为 16MHz
    // IRCF<2:0>=111 (16MHz), SWDTEN=0
    OSCCON = 0x70;

    // 延时确保时钟稳定
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
// 发送一个字节，直接位展开消除分支
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
    ws2812_send_byte(color.r);
    ws2812_send_byte(color.g);
    ws2812_send_byte(color.b);
}

static void ws2812_reset(void) {
    RB1 = 0;
    delay_ms(1);   // >50us
}

void ws2812_update_RGB(RGB_t *leds, unsigned char num) {
    unsigned char i;
    unsigned char key_was_pressed = 0;

    // 发送前检查按键状态
    if (RA0 == 0) {
        key_was_pressed = 1;
    }

    GIE = 0;
    for (i = 0; i < num; i++) {
        ws2812_send_color(leds[i]);
    }
    ws2812_reset();
    GIE = 1;

    // 发送后如果之前检测到按键，且按键已释放，立即处理
    if (key_was_pressed && RA0 == 1) {
        EffectMode_t next_mode = (current_effect + 1) % EFFECT_COUNT;
        effect_execute(next_mode);
    }
}

// ========== GPIO Initialization ==========
static void ws2812_gpio_init(void) {
    // 配置 RA0 为输入（按键）
    TRISA |= (1 << 0);    // RA0 设为输入

    // ANSEL0 清零 bit0（禁用 RA0 模拟功能）
    ANSEL0 &= ~(1 << 0);

    // ANSEL1 (94H): Bit1 = ANS9 = RB1, set to 0 for digital I/O
    ANSEL1 &= ~(1 << 1);

    // TRISB (05H): Bit1 = TRISB1, set to 0 for output
    TRISB &= ~(1 << 1);

    // RB1 = 0 initial low
    RB1 = 0;
}

// ========== Key Function (RA0, active low) ==========
static unsigned char power_state = 1;  // 1=开, 0=关
static unsigned char key_press_counter = 0;  // 按键计数器
static unsigned char key_pressed = 0;  // 按键已按下标志

void key_scan(void) {
    if (RA0 == 0) {
        // 按键按下
        if (!key_pressed) {
            delay_ms(20);  // 消抖
            if (RA0 == 0) {
                key_pressed = 1;
                key_press_counter = 0;
            }
        } else {
            // 按键持续按下，计数
            if (key_press_counter < 255) {
                key_press_counter++;
            }
            // 长按检测：约1.5秒（150次10ms循环）
            if (key_press_counter == 150) {
                // 长按：切换开关
                power_state = !power_state;
                if (!power_state) {
                    // 关闭：全黑
                    unsigned char i;
                    for (i = 0; i < LED_COUNT; i++) {
                        leds[i].r = 0;
                        leds[i].g = 0;
                        leds[i].b = 0;
                    }
                    ws2812_update_RGB(leds, LED_COUNT);
                }
                // 等待按键释放
                while (RA0 == 0);
                key_pressed = 0;
                key_press_counter = 0;
            }
        }
    } else {
        // 按键释放
        if (key_pressed) {
            if (key_press_counter < 150) {
                // 短按：切换效果
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
    // 必须首先设置系统时钟到 16MHz
    system_clock_init();

    // WPUA (88H): Bit0 = WPUA0, set to 1 for pull-up
    WPUA |= (1 << 0);

    // Initialize GPIO for WS2812
    ws2812_gpio_init();

    // 初始化效果
    effect_init();

    // 主循环
    unsigned int update_counter = 0;
    while (1) {
        // 扫描按键
        key_scan();

        // 更新效果（每 10ms）
        update_counter++;
        if (update_counter >= 10) {
            update_counter = 0;

            // 只有在开机状态下才更新效果
            if (power_state) {
                // 调用当前效果的更新函数
                effects_update();
            }

            // 发送数据到 LED
            ws2812_update_RGB(leds, LED_COUNT);
        }

        // 短暂延时，避免过度占用 CPU
        delay_ms(1);
    }
}
