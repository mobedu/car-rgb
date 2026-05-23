#include <sc.h>
#include "config.h"
#include "effects_new.h"

volatile EffectMode_t current_effect = EFFECT_SLOW_FLASH;
RGB_t leds[LED_COUNT];
unsigned char g_color_index = 0;

static const unsigned char c00=255,c01=0,c02=0,c10=0,c11=255,c12=0,c20=0,c22=255;
static const unsigned char c30=255,c31=255,c32=0,c40=255,c42=255,c50=0,c51=255,c52=255;
static const unsigned char c60=255,c61=128,c62=0,c70=255,c72=128,c80=128,c81=255,c82=0;
static const unsigned char c90=255,c91=255,c92=255;

static unsigned char get_color(unsigned char idx, unsigned char comp) {
    if (idx == 0) return comp==0?c00:comp==1?c01:c02;
    if (idx == 1) return comp==0?c10:comp==1?c11:c12;
    if (idx == 2) return comp==0?c20:comp==1?c01:c22;
    if (idx == 3) return comp==0?c30:comp==1?c31:c32;
    if (idx == 4) return comp==0?c40:comp==1?c31:c42;
    if (idx == 5) return comp==0?c50:comp==1?c51:c52;
    if (idx == 6) return comp==0?c60:comp==1?c61:c62;
    if (idx == 7) return comp==0?c70:comp==1?c31:c72;
    if (idx == 8) return comp==0?c80:comp==1?c81:c82;
    return comp==0?c90:comp==1?c91:c92;
}

static void fill_led(unsigned char r, unsigned char g, unsigned char b) {
    unsigned char i;
    for (i = 0; i < LED_COUNT; i++) {
        leds[i].r = r; leds[i].g = g; leds[i].b = b;
    }
}

static unsigned char sfl_cnt = 0, sfl_st = 0;
void slow_flash_init(void) {
    sfl_cnt = sfl_st = 0;
    fill_led(get_color(g_color_index, 0), get_color(g_color_index, 1), get_color(g_color_index, 2));
}
void slow_flash_update(void) {
    if (++sfl_cnt < 50) return;
    sfl_cnt = 0;
    sfl_st = !sfl_st;
    fill_led(sfl_st ? get_color(g_color_index, 0) : 0, sfl_st ? get_color(g_color_index, 1) : 0, sfl_st ? get_color(g_color_index, 2) : 0);
}

static unsigned char ffl_cnt = 0, ffl_st = 0;
void fast_flash_init(void) {
    ffl_cnt = ffl_st = 0;
    fill_led(get_color(g_color_index, 0), get_color(g_color_index, 1), get_color(g_color_index, 2));
}
void fast_flash_update(void) {
    if (++ffl_cnt < 10) return;
    ffl_cnt = 0;
    ffl_st = !ffl_st;
    fill_led(ffl_st ? get_color(g_color_index, 0) : 0, ffl_st ? get_color(g_color_index, 1) : 0, ffl_st ? get_color(g_color_index, 2) : 0);
}

static unsigned char br_val = 0, br_dir = 1, br_col = 0, br_cnt = 0;
void breath_10color_init(void) {
    br_val = 0; br_dir = 1; br_col = 0;
}
void breath_10color_update(void) {
    if (++br_cnt < 2) return;
    br_cnt = 0;
    br_val += br_dir * 8;
    if (br_val >= 250) { br_val = 250; br_dir = -1; }
    else if (br_val <= 0) { br_val = 0; br_dir = 1; br_col = (br_col + 1) % 10; }
    fill_led((br_val * get_color(br_col, 0)) >> 8, (br_val * get_color(br_col, 1)) >> 8, (br_val * get_color(br_col, 2)) >> 8);
}

static unsigned char sr_st = 0, sr_cnt = 0, sr_col = 0;
void slow_rainbow_init(void) {
    sr_st = sr_cnt = sr_col = 0;
}
void slow_rainbow_update(void) {
    if (++sr_cnt < 50) return;
    sr_cnt = 0;
    sr_st = !sr_st;
    if (!sr_st) sr_col = (sr_col + 1) % 10;
    fill_led(sr_st ? get_color(sr_col, 0) : 0, sr_st ? get_color(sr_col, 1) : 0, sr_st ? get_color(sr_col, 2) : 0);
}

static unsigned char fr_st = 0, fr_cnt = 0, fr_col = 0;
void fast_rainbow_init(void) {
    fr_st = fr_cnt = fr_col = 0;
}
void fast_rainbow_update(void) {
    if (++fr_cnt < 10) return;
    fr_cnt = 0;
    fr_st = !fr_st;
    if (!fr_st) fr_col = (fr_col + 1) % 10;
    fill_led(fr_st ? get_color(fr_col, 0) : 0, fr_st ? get_color(fr_col, 1) : 0, fr_st ? get_color(fr_col, 2) : 0);
}

static unsigned char plc_st = 0, plc_cnt = 0;
void police_new_init(void) {
    plc_st = plc_cnt = 0;
    fill_led(255, 0, 0);
}
void police_new_update(void) {
    if (++plc_cnt < 5) return;
    plc_cnt = 0;
    plc_st = !plc_st;
    fill_led(plc_st ? 255 : 0, 0, plc_st ? 0 : 255);
}

static unsigned char run_pos = 0, run_st = 0, run_lp = 0, run_cnt = 0;
void runner_init(void) {
    run_pos = run_st = run_lp = run_cnt = 0;
    fill_led(0, 0, 0);
}
void runner_update(void) {
    if (++run_cnt < 3) return;
    run_cnt = 0;
    unsigned char i;
    if (run_st == 0) {
        fill_led(0, 0, 0);
        leds[run_pos].r = get_color(run_pos % LED_COUNT, 0);
        leds[run_pos].g = get_color(run_pos % LED_COUNT, 1);
        leds[run_pos].b = get_color(run_pos % LED_COUNT, 2);
        if (++run_pos >= LED_COUNT) { run_pos = 0; run_st = 1; run_lp = 0; }
    } else if (run_st == 1) {
        fill_led(0, 0, 0);
        for (i = 0; i < LED_COUNT; i++) {
            unsigned char p = (run_pos + i) % LED_COUNT;
            leds[p].r = get_color((run_pos + i) % LED_COUNT, 0);
            leds[p].g = get_color((run_pos + i) % LED_COUNT, 1);
            leds[p].b = get_color((run_pos + i) % LED_COUNT, 2);
        }
        if (++run_pos >= LED_COUNT) { run_pos = 0; if (++run_lp >= 2) { run_st = 2; run_pos = 0; } }
    } else {
        if (run_pos < LED_COUNT) { leds[run_pos].r = leds[run_pos].g = leds[run_pos].b = 0; run_pos++; }
        else { run_pos = 0; run_st = 0; run_lp = 0; }
    }
}

static void (*init_tab[7])(void) = {slow_flash_init, fast_flash_init, breath_10color_init, slow_rainbow_init, fast_rainbow_init, police_new_init, runner_init};
static void (*update_tab[7])(void) = {slow_flash_update, fast_flash_update, breath_10color_update, slow_rainbow_update, fast_rainbow_update, police_new_update, runner_update};

void effect_new_init(void) { init_tab[current_effect](); }
void effect_new_execute(EffectMode_t m) { current_effect = m; init_tab[m](); }
void effects_new_update(void) { update_tab[current_effect](); }