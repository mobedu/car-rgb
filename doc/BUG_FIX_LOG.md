# Bug修复记录

## 2025-XX-XX - V1.02 太阳能板+电池电压检测功能

### 新增功能

#### 1. 太阳能板光线检测
- 根据光照强度自动开关灯
- 光线强(>2.3V) → 禁止开灯
- 光线弱(<0.9V) → 允许开灯

#### 2. 电池动态亮度
- 根据电池电压调整LED最大亮度
- 4.2V = 255 (最亮)
- 3.5V = 90 (低电压保护)
- 电压下降时亮度缓降(5分钟从当前降到目标)

---

### 代码修改汇总

#### config.h
```c
// ADC配置
#define ADC_REF_MV       2400     // 参考电压2.4V
#define ADC_RESOLUTION   4095     // 12位ADC

// 电池分压: 300K+100K, 分压比0.25
#define BAT_R1_OHM       300000
#define BAT_R2_OHM       100000

// 太阳能分压: 20K+10K, 分压比0.333
#define SOLAR_R1_OHM       20000
#define SOLAR_R2_OHM       10000
```

#### power.c/h
```c
// ADC初始化
void adc_init(void) {
    ADON = 1;
    ADCON1 = 0x30;      // VDD/VSS, 左对齐
    ADCON2 = 0x94;      // FOSC/32
    ANSEL0 = 0x0C;     // RA2,RA3作模拟输入
}

// 读取电池ADC (通道2)
unsigned int battery_read_adc(void) {
    ADCON0 = 0x08;   // CHS=2
    // 等待采集时间
    GO = 1;
    while(GO);
    return (ADRESH<<8) | ADRESL;
}

// 读取太阳能ADC (通道3)
unsigned int solar_read_adc(void) {
    ADCON0 = 0x0C;   // CHS=3
    // ...
}

// 电池亮度查表
static const unsigned char battery_brightness_curve[] = {
    255, 200, 186, 178, 170, 162, 154, 146, 138, 90
};

// 太阳能自动控制 (带迟滞)
void solar_auto_control(void) {
    // ADC > 1000: 强光 → 禁止开灯
    // ADC < 800: 黑暗 → 允许开灯
}
```

#### main.c
```c
// 电池缓降变量
static unsigned int battery_check_counter = 0;
static unsigned char battery_target_brightness = 255;
static unsigned char current_battery_brightness = 255;
static unsigned int brightness_fade_counter = 0;

// 初始化
adc_init();
battery_adc_value = battery_read_adc();
battery_target_brightness = get_battery_brightness(battery_adc_value);
current_battery_brightness = battery_target_brightness;
max_brightness_limit = current_battery_brightness;

// 主循环 - 电池动态亮度
if (power_state && lights_on) {
    // 每1秒: 读取电压,更新目标亮度
    if (++battery_check_counter >= 1000) {
        battery_adc_value = battery_read_adc();
        battery_target_brightness = get_battery_brightness(battery_adc_value);
    }

    // 每5秒: 缓调1亮度
    if (++brightness_fade_counter >= 5) {
        brightness_fade_counter = 0;
        if (current_battery_brightness > battery_target_brightness) {
            current_battery_brightness--;
        } else if (current_battery_brightness < battery_target_brightness) {
            current_brightness++;
        }
    }
    max_brightness_limit = current_battery_brightness;
}

// 主循环 - 太阳能检测
solar_auto_control();
if (power_state && lights_on && !solar_auto_enabled) {
    power_off_leds(leds);
    ws2812_update(leds, LED_COUNT);
}
```

#### effects.c
```c
// 全局亮度上限
unsigned char max_brightness_limit = 255;

// 亮度缩放
static void apply_brightness(...) {
    unsigned char limit = max_brightness_limit;
    if (brightness < 10) {
        limit = (limit * brightness) / 10;
    }
    // 应用到RGB
}

// 呼吸模式(模式4)也要应用动态亮度
case 4:
    {
        unsigned char dim;
        dim = (br_val * max_brightness_limit) >> 8;
        r = (pal_r[br_col] * dim) >> 8;
        // ...
    }
```

---

### 硬件连接

| 引脚 | 功能 | ADC通道 |
|------|------|--------|
| RA2 | 电池电压检测 | AN2 |
| RA3 | 太阳能板检测 | AN3 |

---

### 注意事项

1. **ADC通道**: 使用AN2(RA2)和AN3(RA3)，不是AN9和AN11
2. **亮度缓降**: 从255降到90需要约275秒(~4.6分钟)
3. **太阳能迟滞**: 800/1000阈值避免闪烁