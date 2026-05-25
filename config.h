#ifndef __CONFIG_H
#define __CONFIG_H

#include <sc.h>
#define USE_16MHZ        1
#define LED_COUNT        10

// ========== 引脚定义 (按 PIN.md，SC8F073更新) ==========
#define PIN_KEY_BIT     5    // RA5 bit position - 按键
#define PIN_RF_DATA_BIT 0    // RA0 bit position - RF数据
#define PIN_SHUT_BIT    4    // RB4 bit position - RF SHUT
#define PIN_LED_POWER_BIT 1  // RA1 bit position - WS2812供电控制
#define PIN_WS2812B_BIT 7    // RB7 bit position - WS2812数据
#define PIN_DEBUG_BIT    3    // RB3 bit position - 调试测试引脚

// 震动传感器引脚
#define PIN_VIBR_BIT     0    // RB0 - 震动传感器输入 (与电池ADC共享，需确认硬件)
#define PIN_VIBR_READ()  ((PORTB >> PIN_VIBR_BIT) & 1)

#define PIN_KEY_READ()  ((PORTA >> PIN_KEY_BIT) & 1)
#define PIN_SHUT_LOW()  PORTB &= ~(1 << PIN_SHUT_BIT)
#define PIN_SHUT_HIGH() PORTB |= (1 << PIN_SHUT_BIT)
#define PIN_LED_POWER_ON()  PORTA |= (1 << PIN_LED_POWER_BIT)
#define PIN_LED_POWER_OFF() PORTA &= ~(1 << PIN_LED_POWER_BIT)
#define PIN_WS2812B_LOW()  PORTB &= ~(1 << PIN_WS2812B_BIT)
#define PIN_WS2812B_HIGH() PORTB |= (1 << PIN_WS2812B_BIT)

// ========== ADC 配置 ==========
#define PIN_BAT_ADC      RA2      // 电池电压检测
#define PIN_CDS_ADC     RA3      // 太阳能板电压检测
#define ADC_REF_MV       2400     // 参考电压 2.4V
#define ADC_RESOLUTION   4095     // 12位 ADC (0-4095)

// ADC值转电压 (mV)
#define ADC_TO_MV(adc)    ((unsigned int)(adc) * ADC_REF_MV / ADC_RESOLUTION)
// 电压(mV)转ADC值
#define MV_TO_ADC(mv)     ((unsigned int)(mv) * ADC_RESOLUTION / ADC_REF_MV)

// 太阳能板分压: R1=20K, R2=10K, 分压比 = 10K/(20K+10K) = 0.333
#define SOLAR_R1_OHM       20000
#define SOLAR_R2_OHM       10000
#define SOLAR_DIVIDER      ((SOLAR_R2_OHM * 1000) / (SOLAR_R1_OHM + SOLAR_R2_OHM))

// 太阳能板阈值 (mV)
#define SOLAR_DARK_THRESH_MV    900    // 0.9V - 光线暗开灯
#define SOLAR_BRIGHT_THRESH_MV  2300    // 2.3V - 光线强关灯


// 电池分压: R1=300K, R2=100K, 分压比 = 100K/(300K+100K) = 0.25
// 测量范围: 2.4V / 0.25 = 9.6V (实际需要 0-4.2V)
#define BAT_R1_OHM       300000
#define BAT_R2_OHM       100000
#define BAT_DIVIDER      ((BAT_R2_OHM * 1000) / (BAT_R1_OHM + BAT_R2_OHM))

// 光敏分压: R1=30K, R2=10K, 分压比 = 10K/(30K+10K) = 0.25
// 测量范围: 2.4V / 0.25 = 9.6V (实际需要 0-6V)
#define CDS_R1_OHM       30000
#define CDS_R2_OHM       10000
#define CDS_DIVIDER      ((CDS_R2_OHM * 1000) / (CDS_R1_OHM + CDS_R2_OHM))

// ========== 电池保护参数 ==========
#define BAT_PROTECT_MV   2700     // 低电压保护 2.7V
#define BAT_RECOVER_MV   3100     // 恢复电压 3.1V
#define BAT_MAX_MV       4200     // 电池满电 4.2V
#define BAT_MIN_MV       0        // 电池最低 0V

// ========== 光敏参数 ==========
#define CDS_DARK_THRESH  1000     // 暗阈值 (ADC值)
#define CDS_BRIGHT_THRESH 3000    // 亮阈值 (ADC值)

// ========== 外设使能 ==========
#define ENABLE_BATTERY_MONITOR    1
#define ENABLE_CDS_SENSOR         1
#define ENABLE_VIBRATION_SENSOR   1
#define ENABLE_RF433_CONTROL      1
#define ENABLE_POWER_MANAGEMENT   1

#define BATTERY_CHECK_INTERVAL    5000
#define CDS_CHECK_INTERVAL        1000
#define AUTO_SLEEP_TIMEOUT        30

// ========== 电池-亮度参数 (在power.c中定义查表) ==========
#define BAT_MAX_BRIGHTNESS  255
#define BAT_MIN_BRIGHTNESS  50   // 最低不低于50

// ========== 电池规格 ==========
#define BAT_CAPACITY_MAH          1800

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB_t;

extern RGB_t leds[LED_COUNT];
extern unsigned char color_index;

#endif