# 外设集成说明

## 概述

本文档说明如何将电池电压检测、RF433 接收、震动开关和低功耗管理集成到现有项目中。

---

## 新增文件

| 文件 | 功能 | 行数 |
|------|------|------|
| battery.h | 电池检测头文件 | ~40 |
| battery.c | 电池电压检测实现 | ~120 |
| rf433.h | RF433 接收头文件 | ~50 |
| rf433.c | RF433 接收实现 | ~160 |
| vibration.h | 震动开关头文件 | ~25 |
| vibration.c | 震动开关实现 | ~45 |
| power.h | 电源管理头文件 | ~55 |
| power.c | 低功耗管理实现 | ~140 |
| iservices.h | 中断服务头文件 | ~20 |
| iservices.c | 中断服务实现 | ~40 |
| **总计** | | **~695 行** |

---

## 引脚分配

| 功能 | 引脚 | 配置 |
|------|------|------|
| WS2812B DIN | RB1 | 数字输出 |
| 按键 | RA0 | 数字输入, 上拉 |
| 电池检测 (ADC) | RA2 (AN10) | 模拟输入 |
| RF433 接收 | RA3 (AN11) | 数字输入, INT0 |
| 震动开关 | RA4 (AN12) | 数字输入, IOC |

---

## 硬件连接

### 电池电压检测
```
电池正极 ── R1(100k) ──┬── AN10(RA2)
                        │
                        └── R2(47k) ── GND
```
- 分压比: R2/(R1+R2) = 47k/147k ≈ 0.32
- 测量范围: 0-15.6V (使用 5V 参考)

### RF433 接收器
```
RF433 模块 VCC ── 5V
RF433 模块 GND ── GND
RF433 模块 DATA ── RA3 (INT0)
RF433 模块 ANT ── 天线 (17cm 铜线)
```

### 震动开关
```
震动开关 一端 ── 5V
震动开关 另一端 ── RA4
内部下拉电阻: 10k-100k
```

---

## 代码集成步骤

### 1. 更新 SCW 项目配置

将新文件添加到 `car-rgb.scw`:

```
[FILE]
SourceFile=battery.c
SourceFile=rf433.c
SourceFile=vibration.c
SourceFile=power.c
SourceFile=iservices.c
SourceFile=main.c
SourceFile=effects_new.c
HeadFile=config.h
HeadFile=ws2812.h
HeadFile=effects_new.h
HeadFile=battery.h
HeadFile=rf433.h
HeadFile=vibration.h
HeadFile=power.h
HeadFile=iservices.h
```

### 2. 在 main.c 中添加初始化

```c
#include "battery.h"
#include "rf433.h"
#include "vibration.h"
#include "power.h"
#include "iservices.h"

void System_Init(void) {
    // 系统时钟初始化
    system_clock_init();

    // 使能全局中断
    GIE = 1;
    PEIE = 1;

    // GPIO 初始化
    ws2812_gpio_init();

    // 外设初始化
#if ENABLE_BATTERY_MONITOR
    battery_adc_init();
#endif

#if ENABLE_POWER_MANAGEMENT
    power_manager_init();
#endif

    // 效果初始化
#if USE_NEW_EFFECTS
    effect_new_init();
#endif
}
```

### 3. 在主循环中添加处理逻辑

```c
void main(void) {
    System_Init();

    unsigned int update_counter = 0;
    unsigned int battery_counter = 0;

    while (1) {
        asm("clrwdt");

        // 按键扫描
        key_scan();

        // RF433 命令处理
        if (rf433_has_command()) {
            rf433_process_command();
            power_reset_idle_counter();
        }

        // 震动检测
        if (vibration_detected()) {
            // 震动唤醒后的处理
            power_reset_idle_counter();
        }

        // 电池电压检测
#if ENABLE_BATTERY_MONITOR
        battery_counter++;
        if (battery_counter >= BATTERY_CHECK_INTERVAL / 10) {
            battery_counter = 0;
            battery_update_brightness_limit();
        }
#endif

        // 效果更新
        update_counter++;
        if (update_counter >= 10) {
            update_counter = 0;

            if (power_get_state() == POWER_STATE_ACTIVE) {
#if USE_NEW_EFFECTS
                effects_new_update();
#endif
                ws2812_update_RGB(leds, LED_COUNT);
            }

            // 更新空闲计数器
#if ENABLE_POWER_MANAGEMENT
            power_update_idle_counter();
#endif
        }

        // 检查是否需要进入睡眠
#if ENABLE_POWER_MANAGEMENT
        if (power_get_state() != POWER_STATE_ACTIVE) {
            power_enter_sleep(SLEEP_MODE_SLEEP);
            // 唤醒后重新初始化
            System_Init();
        }
#endif

        delay_ms(1);
    }
}
```

---

## ROM 资源估算

| 模块 | 估算 ROM | 说明 |
|------|---------|------|
| 原有代码 | ~3KB | main.c + effects_new.c + ws2812 |
| 电池检测 | ~200B | ADC 初始化 + 电压计算 |
| RF433 接收 | ~400B | 状态机 + 中断处理 |
| 震动开关 | ~100B | IOC 中断处理 |
| 电源管理 | ~300B | 睡眠/唤醒逻辑 |
| 中断服务 | ~100B | ISR 集成 |
| **总计** | **~4.1KB** | SC8F072(4K) 紧张，建议用 8K 版本 |

---

## 芯片选型建议

### SC8F072 变体
| 型号 | ROM | RAM | 评估 |
|------|-----|-----|------|
| SC8F072 | 4K | 256B | ❌ ROM 不足 |
| SC8F072A | 8K | 256B | ✅ 推荐 |
| SC8F074 | 8K | 512B | ✅ 更好 |
| SC8F076 | 16K | 512B | ✅ 富裕 |

### 替代芯片
| 芯片 | ROM | RAM | 价格 |
|------|-----|-----|------|
| SC8F074 | 8K | 512B | 低 |
| SC8F076 | 16K | 512B | 中 |
| SC8F084 | 16K | 1KB | 中高 |

**推荐**: SC8F074 或 SC8F076

---

## 调试建议

### 1. 电池电压检测
- 检查分压电阻是否正确
- 使用万用表验证 ADC 读数
- 确认 ANSEL 配置

### 2. RF433 接收
- 使用示波器观察数据波形
- 调整时序参数
- 确认 INT0 中断触发

### 3. 震动开关
- 检查下拉电阻
- 测试 IOC 中断触发
- 验证唤醒功能

### 4. 低功耗
- 测量休眠电流
- 确认唤醒源工作
- 验证时钟切换

---

## 注意事项

1. **WDT 喂狗**: 所有阻塞操作必须喂狗
2. **中断优先级**: RF433 时序需要较高优先级
3. **时序调整**: 根据实际 RF433 模块调整时序参数
4. **电池保护**: 欠压保护逻辑需要根据实际电池特性调整
5. **睡眠唤醒**: SLEEP 唤醒后必须重新初始化系统

---

## 下一步

1. 选择合适的芯片型号
2. 硬件焊接测试
3. 软件编译烧录
4. 功能测试调优