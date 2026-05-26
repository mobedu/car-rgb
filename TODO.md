# TODO - 待实现功能

## 遥控器按键功能

### 已实现 ✓

| 按键 | 功能 | 状态 |
|------|------|------|
| ON | 开灯 | ✓ |
| OFF | 关灯 | ✓ |
| MODE 1-8 | 8种灯效模式 | ✓ |
| 亮度+ | 亮度增加 | ✓ V2.0修复 |
| 亮度- | 亮度减少 | ✓ V2.0修复 |

### 未实现 ❌

| 按键 | 功能 | 说明 |
|------|------|------|
| 4H | 4小时定时 | 定时4小时后自动关灯 |
| 6H | 6小时定时 | 定时6小时后自动关灯 |
| 8H | 8小时定时 | 定时8小时后自动关灯 |
| 定时关闭 | 取消定时 | 取消已设置的定时 |
| RESET | 系统复位 | 恢复出厂设置 |

## 其他待办

### 高优先级

- [ ] 测试低电压保护功能（2.7V锁定/3.1V解锁）

### 中优先级

- [x] 呼吸模式严重BUG - 已修复
- [ ] 优化按键长按2秒判断逻辑
- [ ] 添加电池百分比显示（可选debug功能）

### 低优先级

- [ ] 添加闪烁提示低电压锁定状态
- [ ] 添加充电指示灯功能

---

## 技术说明

### 定时功能实现思路

```c
// 需要添加变量
static unsigned int power_off_timer = 0;  // 定时计数器
static unsigned char timer_hours = 0;      // 已设置的定时小时数

// 4H/6H/8H 命令处理
case RF_CMD_TIME_4H: timer_hours = 4;  power_off_timer = 0;  break;
case RF_CMD_TIME_6H: timer_hours = 6;  power_off_timer = 0;  break;
case RF_CMD_TIME_8H: timer_hours = 8;  power_off_timer = 0;  break;
case RF_CMD_TIME_OFF: timer_hours = 0; break;

// 主循环每秒检查
if (timer_hours > 0) {
    power_off_timer++;
    // 3600秒 * 小时数
    if (power_off_timer >= (unsigned long)timer_hours * 3600) {
        lights_on = 0;
        timer_hours = 0;
    }
}
```

### RESET 功能实现思路

```c
case RF_CMD_RESET:
    // 恢复出厂设置
    effect_mode = 1;
    brightness = BRIGHTNESS_DEFAULT;
    color_index = 9;
    battery_low_voltage_lock = 0;  // 清除锁定
    timer_hours = 0;
    break;
```

---

## 版本历史

### V2.1 (ef44b17)
- WS2812新灯带时序适配: S0=2, S1=5个__ws_dly=0
- 修复颜色解码错误问题

### V2.0 (c8373f8)
- apply_brightness四舍五入修复
- dim即时响应机制
- volatile声明完善
- 修复呼吸模式BUG

### V1.02b (1a085a9)
- 优化RA1电源控制