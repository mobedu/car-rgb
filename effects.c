#include "effects.h"

// ========== 10色调色板 (红蓝绿橙青紫黄粉红天蓝混白) ==========
static const unsigned char pal_r[10] = {255,0,0,255,0,128,255,255,0,255};
static const unsigned char pal_g[10] = {0,0,255,128,255,0,255,0,128,255};
static const unsigned char pal_b[10] = {0,255,0,0,255,255,0,128,255,255};

// ========== 全局状态 ==========
unsigned char color_index = 9;               // 默认混白

static unsigned char effect_mode = 1;        // 当前模式 1-8
static unsigned char brightness = BRIGHTNESS_DEFAULT;
static unsigned int  tick = 0;               // 动画计时器 (~1ms/tick)

// ========== 模式1: 常亮 ==========
// 无动画状态，每次update重新渲染（跟随亮度变化）

// ========== 模式2: 慢闪 (~1Hz) ==========
static unsigned char sf_on = 1;
#define SLOW_FLASH_MS  250

// ========== 模式3: 快闪 (~4Hz) ==========
static unsigned char ff_on = 1;
#define FAST_FLASH_MS  125

// ========== 模式4: 呼吸 (十色自动呼吸) ==========
static unsigned char br_val = 0;
static unsigned char br_dir = 1;   // 1=渐亮, 0=渐暗
static unsigned char br_col = 0;   // 当前颜色索引
#define BREATH_STEP_MS   12
#define BREATH_STEP_VAL  3

// ========== 模式5: 慢闪幻彩 ==========
static unsigned char sr_on = 1;
static unsigned char sr_col = 0;
#define SLOW_RAINBOW_MS  250

// ========== 模式6: 快闪幻彩 ==========
static unsigned char fr_on = 1;
static unsigned char fr_col = 0;
#define FAST_RAINBOW_MS  125

// ========== 模式7: 警示 (红蓝交替快闪) ==========
static unsigned char pol_state = 0;  // 0=红, 1=蓝
#define POLICE_MS  62

// ========== 模式8: 跑马 ==========
// 阶段0: 追逐(单颗灯珠跑一圈)
// 阶段1: 全部亮旋转2圈
// 阶段2: 逐颗熄灭
static unsigned char mq_phase = 0;   // 0=追逐, 1=旋转, 2=熄灭
static unsigned char mq_pos = 0;
static unsigned char mq_rot_count = 0;
static unsigned char mq_rot_step = 0;
#define MARQUEE_CHASE_MS   200
#define MARQUEE_ROTATE_MS  100
#define MARQUEE_OFF_MS     200

// ========== 亮度缩放 ==========
static void apply_brightness(unsigned char *r, unsigned char *g, unsigned char *b) {
    if (brightness >= 10) return;
    if (brightness == 0) { *r = *g = *b = 0; return; }
    *r = ((unsigned int)(*r) * brightness) / 10;
    *g = ((unsigned int)(*g) * brightness) / 10;
    *b = ((unsigned int)(*b) * brightness) / 10;
}

// ========== 辅助: 全部LED设同一颜色 ==========
static void fill_all(unsigned char r, unsigned char g, unsigned char b) {
    unsigned char i;
    for (i = 0; i < LED_COUNT; i++) {
        leds[i].r = r; leds[i].g = g; leds[i].b = b;
    }
}

// ========== 辅助: 全部LED熄灭 ==========
static void fill_off(void) {
    unsigned char i;
    for (i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
    }
}

// ========== 获取当前颜色(受brightness影响) ==========
static void get_color_dim(unsigned char idx, unsigned char *r, unsigned char *g, unsigned char *b) {
    *r = pal_r[idx]; *g = pal_g[idx]; *b = pal_b[idx];
    apply_brightness(r, g, b);
}

// ========== 模式初始化 ==========
static void mode_init(unsigned char mode) {
    tick = 0;
    switch (mode) {
        case 2: sf_on = 1; break;
        case 3: ff_on = 1; break;
        case 4: br_val = 0; br_dir = 1; br_col = 0; break;
        case 5: sr_on = 1; sr_col = 0; break;
        case 6: fr_on = 1; fr_col = 0; break;
        case 7: pol_state = 0; break;
        case 8: mq_phase = 0; mq_pos = 0; mq_rot_count = 0; mq_rot_step = 0; break;
    }
}

// ========== 公共API ==========

void effects_init(void) {
    color_index = 9;
    effect_mode = 1;
    brightness = BRIGHTNESS_DEFAULT;
    tick = 0;
}

void effects_set_mode(unsigned char mode) {
    if (mode < 1 || mode > 8) return;
    if (mode != effect_mode) {
        effect_mode = mode;
        mode_init(mode);
    } else {
        // 同模式: 模式1-3切颜色, 模式4-8重新初始化动画
        if (mode <= 3) {
            effects_next_color();
        } else {
            mode_init(mode);
        }
    }
}

void effects_next_color(void) {
    if (++color_index >= 10) color_index = 0;
}

void effects_brightness_up(void) {
    if (brightness < 10) brightness++;
}

void effects_brightness_down(void) {
    if (brightness > 1) brightness--;
}

unsigned char effects_get_brightness(void) {
    return brightness;
}

// ========== 每帧更新 ==========
void effects_update(void) {
    unsigned char r, g, b, i;
    tick++;

    switch (effect_mode) {
        // ===== 模式1: 常亮 =====
        case 1:
            get_color_dim(color_index, &r, &g, &b);
            fill_all(r, g, b);
            tick = 0;  // 不需要累积tick
            break;

        // ===== 模式2: 慢闪 =====
        case 2:
            if (tick >= SLOW_FLASH_MS) {
                tick = 0;
                sf_on = !sf_on;
            }
            if (sf_on) {
                get_color_dim(color_index, &r, &g, &b);
                fill_all(r, g, b);
            } else {
                fill_off();
            }
            break;

        // ===== 模式3: 快闪 =====
        case 3:
            if (tick >= FAST_FLASH_MS) {
                tick = 0;
                ff_on = !ff_on;
            }
            if (ff_on) {
                get_color_dim(color_index, &r, &g, &b);
                fill_all(r, g, b);
            } else {
                fill_off();
            }
            break;

        // ===== 模式4: 呼吸 (多色依次) =====
        case 4:
            if (tick >= BREATH_STEP_MS) {
                tick = 0;
                if (br_dir) {
                    // 渐亮阶段：0 → 255
                    if (br_val < 255) {
                        br_val += BREATH_STEP_VAL;
                        if (br_val >= 255) {
                            br_val = 255;
                            br_dir = 0;  // 已达最亮，转向渐暗
                        }
                    }
                } else {
                    // 渐暗阶段：255 → 0
                    if (br_val > 0) {
                        if (br_val >= BREATH_STEP_VAL)
                            br_val -= BREATH_STEP_VAL;
                        else
                            br_val = 0;
                    }
                    // 只有亮度真正为0时才切换颜色
                    if (br_val == 0) {
                        br_dir = 1;  // 转向渐亮
                        if (++br_col >= 10) br_col = 0;
                    }
                }
            }
            // 计算当前颜色强度 (0-255)
            r = ((unsigned int)pal_r[br_col] * br_val) / 255;
            g = ((unsigned int)pal_g[br_col] * br_val) / 255;
            b = ((unsigned int)pal_b[br_col] * br_val) / 255;
            apply_brightness(&r, &g, &b);
            fill_all(r, g, b);
            break;

        // ===== 模式5: 慢闪幻彩 =====
        case 5:
            if (tick >= SLOW_RAINBOW_MS) {
                tick = 0;
                sr_on = !sr_on;
                if (!sr_on) {  // 灭→亮切换时换颜色
                    if (++sr_col >= 10) sr_col = 0;
                }
            }
            if (sr_on) {
                get_color_dim(sr_col, &r, &g, &b);
                fill_all(r, g, b);
            } else {
                fill_off();
            }
            break;

        // ===== 模式6: 快闪幻彩 =====
        case 6:
            if (tick >= FAST_RAINBOW_MS) {
                tick = 0;
                fr_on = !fr_on;
                if (!fr_on) {
                    if (++fr_col >= 10) fr_col = 0;
                }
            }
            if (fr_on) {
                get_color_dim(fr_col, &r, &g, &b);
                fill_all(r, g, b);
            } else {
                fill_off();
            }
            break;

        // ===== 模式7: 警示 (红蓝交替快闪) =====
        case 7:
            if (tick >= POLICE_MS) {
                tick = 0;
                pol_state = !pol_state;
            }
            if (pol_state) {
                // 红
                r = 255; g = 0; b = 0;
            } else {
                // 蓝
                r = 0; g = 0; b = 255;
            }
            apply_brightness(&r, &g, &b);
            fill_all(r, g, b);
            break;

        // ===== 模式8: 跑马 =====
        case 8: {
            unsigned int threshold;
            if (mq_phase == 1)
                threshold = MARQUEE_ROTATE_MS;
            else if (mq_phase == 0)
                threshold = MARQUEE_CHASE_MS;
            else
                threshold = MARQUEE_OFF_MS;

            if (tick < threshold) break;
            tick = 0;

            if (mq_phase == 0) {
                // 追逐阶段: 每次亮一颗灯珠（不同颜色），上一颗灭
                fill_off();
                get_color_dim(mq_pos % 10, &r, &g, &b);
                leds[mq_pos].r = r;
                leds[mq_pos].g = g;
                leds[mq_pos].b = b;
                if (++mq_pos >= LED_COUNT) {
                    mq_pos = 0;
                    mq_phase = 1;
                    mq_rot_count = 0;
                    mq_rot_step = 0;
                }
            } else if (mq_phase == 1) {
                // 旋转阶段: 10颗灯珠全部亮，整体旋转2圈
                for (i = 0; i < LED_COUNT; i++) {
                    // 颜色随位置旋转
                    unsigned char ci = (i + mq_rot_step) % LED_COUNT;
                    get_color_dim(ci, &r, &g, &b);
                    leds[i].r = r; leds[i].g = g; leds[i].b = b;
                }
                if (++mq_rot_step >= LED_COUNT) {
                    mq_rot_step = 0;
                    if (++mq_rot_count >= 2) {
                        mq_phase = 2;
                        mq_pos = 0;
                    }
                }
            } else {
                // 熄灭阶段: 逐颗熄灭
                // 先确保当前该灭的已灭
                leds[mq_pos].r = 0;
                leds[mq_pos].g = 0;
                leds[mq_pos].b = 0;
                // 其它位置保持亮（旋转阶段最后的颜色）
                for (i = 0; i < LED_COUNT; i++) {
                    if (i <= mq_pos) {
                        leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
                    }
                }
                if (++mq_pos >= LED_COUNT) {
                    // 全部熄灭，重新开始
                    mq_phase = 0;
                    mq_pos = 0;
                    mq_rot_count = 0;
                    mq_rot_step = 0;
                }
            }
            break;
        }
    }
}
