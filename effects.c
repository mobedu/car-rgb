#include <sc.h>
#include "config.h"
#include "ws2812.h"

// ȫֱ
volatile uint16_t system_tick_ms = 0;
volatile EffectMode_t current_effect = EFFECT_BREATH;
RGB_t leds[LED_COUNT];

// ========== ɫЧ ==========
static unsigned char breath_val = 25;     // ǰ
static signed char breath_dir = 1;         // 1=, -1=䰵
static unsigned char breath_color = 0;     // 0=, 1=, 2=
static unsigned char breath_transition = 0; // ɫ 0-12

void breath_init(void) {
    breath_val = 25;
    breath_dir = 1;
    breath_color = 0;
    breath_transition = 0;
}

void breath_update(void) {
    // ÿ 10ms һ
    static unsigned char counter = 0;
    counter++;
    if (counter < 10) return;
    counter = 0;

    unsigned char r = 0, g = 0, b = 0;

    // ɫ״̬
    if (breath_transition > 0) {
        breath_transition += 2;
        if (breath_transition > 12) {
            breath_transition = 0;
            breath_color = (breath_color + 1) % 3;
            breath_val = 25;
            breath_dir = 1;
        }

        // ɣɫ25->0ɫ0->25
        unsigned char old_val = 25 - breath_transition;
        unsigned char new_val = breath_transition;

        switch (breath_color) {
            case 0: r = old_val; g = new_val; break;
            case 1: g = old_val; b = new_val; break;
            case 2: b = old_val; r = new_val; break;
        }
    }
    // ״̬
    else {
        // 
        breath_val += breath_dir * 10;

        if (breath_val >= 250) {
            breath_val = 250;
            breath_dir = -1;
        }
        else if (breath_val <= 25 && breath_dir < 0) {
            // ʼ
            breath_transition = 1;
            breath_val = 25;
        }

        // ݵǰɫRGB
        switch (breath_color) {
            case 0: r = breath_val; break;
            case 1: g = breath_val; break;
            case 2: b = breath_val; break;
        }
    }

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }
}

// ========== ˸Ч ==========
#define TWINKLE_COUNT  8  // ͬʱ˸

typedef struct {
    unsigned char pos;    // λ
    unsigned char phase;  // ˸λ
    unsigned char speed;  // ˸ٶ
} TwinkleStar_t;

static TwinkleStar_t stars[TWINKLE_COUNT];
static unsigned char twinkle_counter = 0;

void twinkle_init(void) {
    // ʼеΪɫ
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    // ѡλúͲ
    for (unsigned char i = 0; i < TWINKLE_COUNT; i++) {
        stars[i].pos = (system_tick_ms + i * 29) % LED_COUNT;
        stars[i].phase = (system_tick_ms + i * 17) % 100;
        stars[i].speed = 2 + ((system_tick_ms + i * 11) % 4);
    }
    twinkle_counter = 0;
}

void twinkle_update(void) {
    // ÿ 50ms һΣӿٶȣ
    twinkle_counter++;
    if (twinkle_counter < 5) return;
    twinkle_counter = 0;

    // е
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }

    // ÿ
    for (unsigned char i = 0; i < TWINKLE_COUNT; i++) {
        // λ
        stars[i].phase += stars[i].speed;
        if (stars[i].phase >= 100) {
            stars[i].phase = 0;
            // λúͲ
            stars[i].pos = (stars[i].pos + 13) % LED_COUNT;
            stars[i].speed = 2 + ((stars[i].speed + i) % 4);
        }

        // ȣƽĽ䣩
        unsigned char brightness;
        if (stars[i].phase < 50) {
            // أ0-255
            brightness = (stars[i].phase * 5) + (stars[i].phase * 3 / 10);
        } else {
            // ½أ255-0
            brightness = ((100 - stars[i].phase) * 5) + ((100 - stars[i].phase) * 3 / 10);
        }

        // ɫ
        unsigned char color = (stars[i].pos + i) % 3;
        if (color == 0) {
            leds[stars[i].pos].r = brightness;
        } else if (color == 1) {
            leds[stars[i].pos].g = brightness;
        } else {
            leds[stars[i].pos].b = brightness;
        }
    }
}

// ========== ׷Ч ==========
#define CHASE_SPEED  2  // ׷ٶ
static unsigned char chase_pos = 0;
static unsigned char chase_color_idx = 0;  // 0=, 1=, 2=, 3=, 4=, 5=

void chase_init(void) {
    chase_pos = 0;
    chase_color_idx = 0;
    // LED
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}

void chase_update(void) {
    // ÿ 50ms һ
    static unsigned char counter = 0;
    counter++;
    if (counter < CHASE_SPEED * 10) return;
    counter = 0;

    // е
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }

    // ݵǰɫɫ
    unsigned char r = 0, g = 0, b = 0;
    switch (chase_color_idx) {
        case 0: r = 255; g = 0; b = 0; break;   // 
        case 1: r = 0; g = 255; b = 0; break;   // 
        case 2: r = 0; g = 0; b = 255; break;   // 
        case 3: r = 255; g = 255; b = 0; break; // 
        case 4: r = 255; g = 0; b = 255; break; // 
        case 5: r = 0; g = 255; b = 255; break; // 
    }

    // Բ׷𣺵 3 ĵ
    for (unsigned char i = 0; i < 3; i++) {
        unsigned char pos = (chase_pos + i) % LED_COUNT;
        leds[pos].r = r;
        leds[pos].g = g;
        leds[pos].b = b;
    }

    // λ
    unsigned char old_pos = chase_pos;
    chase_pos = (chase_pos + 1) % LED_COUNT;

    // ÿһȦлɫ
    if (chase_pos < old_pos) {
        chase_color_idx = (chase_color_idx + 1) % 6;
    }
}

// ========== 扩散效果 ==========
static unsigned char expand_size = 0;
static signed char expand_dir = 1;
static unsigned char expand_r = 255, expand_g = 0, expand_b = 0;
static unsigned char expand_seed = 1;

static unsigned char random_value(unsigned char seed) {
    static unsigned short rand_state = 12345;
    rand_state = rand_state * 1103515245 + seed * 257;
    return (unsigned char)(rand_state >> 8);
}

void expand_init(void) {
    expand_size = 0;
    expand_dir = 1;
    expand_r = 255;
    expand_g = 0;
    expand_b = 0;
    expand_seed = 1;
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}

void expand_update(void) {
    static unsigned char counter = 0;
    counter++;
    if (counter < 1) return;
    counter = 0;

    if (expand_size >= LED_COUNT / 2) {
        expand_dir = -1;
    } else if (expand_size == 0 && expand_dir < 0) {
        expand_dir = 1;
        expand_seed += 97;
        expand_r = random_value(expand_seed);
        expand_g = random_value(expand_seed + 67);
        expand_b = random_value(expand_seed + 133);
        if (expand_r < 100 && expand_g < 100 && expand_b < 100) {
            expand_r = 200;
        }
        for (unsigned char i = 0; i < LED_COUNT; i++) {
            leds[i].r = 0;
            leds[i].g = 0;
            leds[i].b = 0;
        }
        return;
    }

    if (expand_dir > 0) {
        unsigned char left = (12 - expand_size + LED_COUNT) % LED_COUNT;
        unsigned char right = (12 + expand_size) % LED_COUNT;
        leds[left].r = expand_r;
        leds[left].g = expand_g;
        leds[left].b = expand_b;
        leds[right].r = expand_r;
        leds[right].g = expand_g;
        leds[right].b = expand_b;
        expand_size++;
    } else {
        unsigned char left = (12 - expand_size + LED_COUNT) % LED_COUNT;
        unsigned char right = (12 + expand_size) % LED_COUNT;
        leds[left].r = 0;
        leds[left].g = 0;
        leds[left].b = 0;
        leds[right].r = 0;
        leds[right].g = 0;
        leds[right].b = 0;
        if (expand_size > 0) expand_size--;
    }
}

// ========== Ч ==========
#define MARQUEE_SPEED  2  // ٶ
static unsigned char marquee_pos = 0;

void marquee_init(void) {
    marquee_pos = 0;
    // ʼ״̬ǰ8ŵ飨ɫ
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    for (unsigned char i = 0; i < 8; i++) {
        leds[i].r = 255;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}

void marquee_update(void) {
    // ÿ 20ms һ
    static unsigned char counter = 0;
    static unsigned char color_index = 0;  // ɫ0=, 1=, 2=, 3=, 4=, 5=

    counter++;
    if (counter < MARQUEE_SPEED * 10) return;
    counter = 0;

    // е
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }

    // ݵǰɫɫ
    unsigned char r = 0, g = 0, b = 0;
    switch (color_index) {
        case 0: r = 255; g = 0; b = 0; break;   // 
        case 1: r = 0; g = 255; b = 0; break;   // 
        case 2: r = 0; g = 0; b = 255; break;   // 
        case 3: r = 255; g = 255; b = 0; break; // 
        case 4: r = 255; g = 0; b = 255; break; // 
        case 5: r = 0; g = 255; b = 255; break; // 
    }

    // 8ŵ
    for (unsigned char i = 0; i < 8; i++) {
        unsigned char pos = (marquee_pos + i) % LED_COUNT;
        leds[pos].r = r;
        leds[pos].g = g;
        leds[pos].b = b;
    }

    // λ
    unsigned char old_pos = marquee_pos;
    marquee_pos = (marquee_pos + 1) % LED_COUNT;

    // ÿһȦص0лɫ
    if (marquee_pos < old_pos) {
        color_index = (color_index + 1) % 6;
    }
}

// ========== Ч ==========
static unsigned char stack_runner = 0;
static unsigned char stack_target = 23;
static unsigned char stack_lit_count = 0;
static unsigned char stack_delay = 0;

void stack_init(void) {
    stack_runner = 0;
    stack_target = 23;
    stack_lit_count = 0;
    stack_delay = 0;
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}

void stack_update(void) {
    // ÿ 10ms һΣǳ죩
    static unsigned char counter = 0;
    counter++;
    if (counter < 1) return;
    counter = 0;

    // ȫʱ
    if (stack_lit_count >= LED_COUNT) {
        stack_delay++;
        if (stack_delay > 30) {
            stack_init();
        }
        return;
    }

    // е
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }

    // Ѷĵ
    for (unsigned char i = stack_target + 1; i < LED_COUNT; i++) {
        leds[i].r = 255;
        leds[i].g = 100;
        leds[i].b = 50;
    }

    // 
    leds[stack_runner].r = 255;
    leds[stack_runner].g = 255;
    leds[stack_runner].b = 0;

    // λ
    stack_runner++;
    if (stack_runner > stack_target) {
        stack_lit_count++;
        if (stack_target > 0) {
            stack_target--;
        }
        stack_runner = 0;
    }
}


// ========== Police Light Effect ==========
static unsigned char police_state = 0;
static unsigned char police_counter = 0;

void police_init(void) {
    police_state = 0;
    police_counter = 0;
    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
}

void police_update(void) {
    police_counter++;
    if (police_counter < 5) return;
    police_counter = 0;

    unsigned char r = 0, g = 0, b = 0;
    if (police_state == 0) {
        r = 255;
    } else {
        b = 255;
    }

    for (unsigned char i = 0; i < LED_COUNT; i++) {
        leds[i].r = r;
        leds[i].g = g;
        leds[i].b = b;
    }

    police_state = !police_state;
}
// ========== Чӿʵ ==========
const static Effect_t effects[] = {
    {breath_init, breath_update},    // Ч
    {twinkle_init, twinkle_update},  // 
    {chase_init, chase_update},      // ׷Ч
    {expand_init, expand_update},    // ɢЧ
    {marquee_init, marquee_update},  // 
    {stack_init, stack_update},
    {police_init, police_update}
};


void effect_init(void) {
    // ʼǰЧ
    if (current_effect < EFFECT_COUNT) {
        effects[current_effect].init();
    }
}

void effect_execute(EffectMode_t mode) {
    current_effect = mode;
    effects[mode].init();
}

// ȫ effects_update  main.c 
void effects_update(void) {
    if (current_effect < EFFECT_COUNT) {
        effects[current_effect].update();
    }
}