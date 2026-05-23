#include <sc.h>
#include "config.h"
#include "VOLT.h"
#include "key.h"
#include "eeprom.h"

// 使用config.h中定义的PWM_PERIOD

// 全局变量
volatile uint8_t timer2_count = 0;
volatile uint8_t Fast_Time = 0;
volatile uint8_t msTime = 0;
volatile uint8_t flash_Time;
uint16_t long_press_timer = 0;           	// 记录按键被按下的时间

uint8_t key_value = 0;

volatile bit     LEDstatus = 0;
volatile bit g_sysmode;                     // 默认开机 1开机 0关机
volatile uint8_t g_mode = 1;                // 亮灯模式 1:常量 2:呼吸 3:快闪 4:慢闪 默认:1
volatile uint16_t PWM_DUTY = 0;             // 当前PWM
volatile bit bat_lvd_flag;           		// 低保状态 1:低保 0:非低保
volatile bit g_night_mode = 0;              // 白天夜晚标志  1:夜晚 0:白天
volatile uint32_t g_night_timer = 0;        // 夜晚模式计数

volatile uint16_t g_solar_check_timer = 0;   // 太阳能板检测时间 (in seconds)
volatile bit timer_off = 0;					// 定时结束标志位 1:结束 0:未结束
volatile bit is_mode_switching;


volatile uint16_t adresult;
volatile uint16_t result;

volatile uint16_t t, read_data;
volatile uint8_t data, read_rom_data;

void Init_System();
void Init_PWM();
void Init_BoostPWM(void);
void EnablePWM(void);
void DisablePWM(void);
void EnableBoostPWM(void);
void DisableBoostPWM(void);
void Init_Timer2();
void setLedPWM(uint16_t duty);
void setBoostPWM(uint16_t duty);

void Sleep_Mode();
void SetLedMode(uint8_t mode);
void SWFlash(uint8_t ms, uint8_t cnt);
void pwm_grad(uint16_t ms);
void flashLED(uint8_t ms);
void handle_constant_mode(void);
void handle_breath_mode(void);
void handle_flash_mode(uint16_t interval);
void handle_combo_mode(uint8_t* state, uint16_t* timer, uint8_t max_states);
void handle_flash_combo(uint8_t count, uint16_t interval);
void handle_auto_cycle_mode(void);

void Init_System() {
    asm("nop");
    asm("clrwdt");
    OSCCON = 0x72;          // 配置振荡为16M, 开WDT:72 关WDT:70
    OPTION_REG = 0;
    asm("clrwdt");
    
    WPUA = 0B00000001;      // 配置上拉
    WPUB = 0B00000000;
    
    TRISA = 0B11111101;     // 配置输入输出   1:输入 0:输出 0B11111101
    TRISB = 0B00000100;     // 0b11111100
    
    PORTA = 0B00000001;     // 配置IO状态   1:高 0:低
    PORTB = 0x00;

    // IOCA = 0b00000001;      // 允许RA0 IO电平变化中断
	INTEDG = 0;				//允许INT外部中断
    // RAIE = 1;               // 允许PORTA端口中断
    INTCON = 0xD0;          // 开总中断，使能外设与INT
    INTF = 0;               // 清除中断标志
    // PORTA;                  // 读取PORTA端口
}

// 初始化LED PWM (RB1引脚)
void Init_PWM(void) {
    TRISB |= (1 << 1);      // 设置 TRISB bit 1 为 1，使 PORTB bit 1 为输入
    // Configure PWM
    PWMCON0 = 0x02;         // Enable PWM1
    PWMCON1 = 0xC0;         // PWM分组，死区，死区分频
    PWMCON2 = 0x00;         // PWM输出极性 1:取反 0:正常

    PWMTL = 0x9F;           // PWM周期低位 100kHz (16MHz/100kHz = 160 = 0x9F+1)
    PWMTH = 0x00;           // PWM周期高位
	
    PWMD1L = 0;             // PWM1占空比低位
    PWMD01H = 0;            // PWM1占空比高位
    TRISB &= ~(1 << 1);     // 清除 TRISB bit 1，将 PORTB bit 1 设置为输出
    PWMCON0 = 0;            // Disable PWM1
}

// 初始化升压PWM (RA2引脚)
void Init_BoostPWM(void) {
    TRISA |= (1 << 2);      // 设置 TRISA bit 2 为 1，使 PORTA bit 2 为输入
    // Configure PWM
    PWMCON0 = 0x04;         // Enable PWM2
    PWMCON1 = 0xC0;         // PWM分组，死区，死区分频
    PWMCON2 = 0x00;         // PWM输出极性 1:取反 0:正常

    PWMTL = 0x9F;           // PWM周期低位 100kHz (16MHz/100kHz = 160 = 0x9F+1)
    PWMTH = 0x00;           // PWM周期高位
	
    PWMD2L = 0;             // PWM2占空比低位
    PWMD23H = 0;            // PWM2占空比高位
    TRISA &= ~(1 << 2);     // 清除 TRISA bit 2，将 PORTA bit 2 设置为输出
    PWMCON0 = 0;            // Disable PWM2
}

// 启用LED PWM输出
void EnablePWM(void) {
    TRISB |= (1 << 1);      // 设置为输入模式
    PWMCON0 = 0x02;         // 启用PWM1
    PWMCON1 = 0xC0;         // PWM分组，死区，死区分频
    PWMCON2 = 0x00;         // PWM输出极性 1:正常
    TRISB &= ~(1 << 1);     // 设置为输出模式
}

// 禁用LED PWM输出并设置IO为低电平
void DisablePWM(void) {
    PWMCON0 = 0;            // 关闭PWM模块
    TRISB |= (1 << 1);      // 设置为输入模式
    TRISB &= ~(1 << 1);     // 设置为输出模式
    LED_PIN = 0;            // 输出低电平
}

// 启用升压PWM输出
void EnableBoostPWM(void) {
    TRISA |= (1 << 2);      // 设置为输入模式
    PWMCON0 = 0x04;         // 启用PWM2
    PWMCON1 = 0xC0;         // PWM分组，死区，死区分频
    PWMCON2 = 0x00;         // PWM输出极性 1:正常
    TRISA &= ~(1 << 2);     // 设置为输出模式
}

// 禁用升压PWM输出并设置IO为低电平
void DisableBoostPWM(void) {
    PWMCON0 = 0;            // 关闭PWM模块
    TRISA |= (1 << 2);      // 设置为输入模式
    TRISA &= ~(1 << 2);     // 设置为输出模式
    PowerPWM_PIN = 0;       // 输出低电平
}

// 设置升压PWM占空比
void setBoostPWM(uint16_t duty) {
    if(duty >= PWM_PERIOD) {
        duty = PWM_PERIOD;
    }
    
    if(duty == 0) {
        // 当占空比为0时，关闭PWM并设置IO为低电平
        DisableBoostPWM();
    } else {
        // 正常PWM输出
        EnableBoostPWM();
        PWMD23H = (uint8_t)(duty >> 8) << 4;
        PWMD2L = (uint8_t)(duty & 0x00FF);
    }
}

// 初始化Timer2
void Init_Timer2(void) {
    // 配置Timer2
    PR2 = 249;              // 设定Timer初始值，定时周期是250*4/16M=62.5uS
    TMR2IF = 0;
    TMR2IE = 1;             // 使能Timer2溢出中断
    T2CON = 0x1D;           // 后分频1:4，Timer2 ON, 预分频4        0x1D 后分频1:4  0x7D 后分频1:16
    
    // INTCON = 0xC0;          // 开启全局和外部中断
    Fast_Time = 0;
}

bit Add_Sign;
uint16_t PWM_Num;
void pwm_grad(uint16_t ms) {
    if(Fast_Time < ms) return;
    
    if(Add_Sign) {
        PWM_Num++;
        if(PWM_Num >= 512) Add_Sign = 0;
    } else {
        PWM_Num--;
        if(PWM_Num == 0) Add_Sign = 1;
    }
    
    setLedPWM(PWM_Num);
    Fast_Time = 0;
}

void flashLED(uint8_t ms) {
    if(Fast_Time < ms) return;
    
    if(LEDstatus) {
        EnablePWM();
        setLedPWM(DEFAULT_PWM);
        LEDstatus = 0;
    } else {
        DisablePWM();
        LEDstatus = 1;
    }
    Fast_Time = 0;
}

// 切换模式闪烁
void SWFlash(uint8_t ms, uint8_t cnt) {
	static uint8_t flash_count = 0;
    if (!is_mode_switching) return;  // 只在模式切换状态时进行闪烁
    if (flash_Time < ms) return;
    
    if(LEDstatus) {
        setLedPWM(128);
        LEDstatus = 0;
        flash_count++;
    } else {
        setLedPWM(0);
        LEDstatus = 1;
    }
    
    if(flash_count >= (cnt + 1)) {
        setLedPWM(0);
        flash_count = 0;
        is_mode_switching = 0;
    }
    
    flash_Time = 0;
}

// 控制LED模式
void handle_constant_mode(void) {
    EnablePWM();
    setLedPWM(PWM_DUTY);
}

void handle_breath_mode(void) {
    pwm_grad(BREATH_STEP_MS);
}

void handle_flash_mode(uint16_t interval) {
    flashLED(interval);
}

void handle_combo_mode(uint8_t* state, uint16_t* timer, uint8_t max_states) {
    (*timer)++;
    
    switch (*state) {
        case 0:
            handle_flash_mode(FAST_BLINK_MS);
            break;
        case 1:
            handle_flash_mode(SLOW_BLINK_MS);
            break;
        default: // state >= 2
            handle_breath_mode();
            break;
    }
    
    if (*timer >= 200) {
        *timer = 0;
        (*state)++;
        if (*state >= max_states) *state = 0;
    }
}

void SetLedMode(uint8_t mode) {
    static uint8_t prev_mode = 0;
    static uint8_t combo_state = 0;
    static uint16_t combo_timer = 0;

    if(prev_mode != mode) {
        prev_mode = mode;
        Fast_Time = 0;
        LEDstatus = 0;
        PWM_Num = 0;
        Add_Sign = 1;
    }

    switch (mode) {
        case 2: handle_breath_mode(); break;
        case 3: handle_flash_mode(FAST_BLINK_MS); break;
        case 4: handle_flash_mode(SLOW_BLINK_MS); break;
        case 5: handle_flash_combo(3, 100); break;
        case 6: handle_flash_combo(3, 1000); break;
        case 7: handle_combo_mode(&combo_state, &combo_timer, 3); break;
        case 8: handle_auto_cycle_mode(); break;
        default: handle_constant_mode(); // 包括case 1和其他情况
    }
}

void setLedPWM(uint16_t duty) {
    if(duty >= PWM_PERIOD) {
        duty = PWM_PERIOD;
    }
    
    if(duty == 0) {
        // 当占空比为0时，关闭PWM并设置IO为低电平
        DisablePWM();
    } else {
        // 正常PWM输出
        EnablePWM();
        PWMD01H = (uint8_t)(duty >> 8) << 4;
        PWMD1L = (uint8_t)(duty & 0x00FF);
    }
}

// 休眠模式
void Sleep_Mode() {
    // 先关闭所有中断和模块
    INTCON = 0;                  
    long_press_timer = 0;

    // 关闭所有未使用的外设模块
    T2CON = 0;                   // 关闭Timer2
    
    // 配置WDT为最长超时时间
    OPTION_REG = 0xCF;           // 设置预分频器分配给WDT，预分频率1:512 (最大值)
    
    // 关闭所有I/O口，设置为输出模式并输出低电平，除了按键输入
    TRISA = 0B00000001;          // 只保留RA0为输入（按键）
    TRISB = 0x00;                // 所有PORTB设为输出
    PORTA = 0x00;                // 所有PORTA输出低电平
    PORTB = 0x00;                // 所有PORTB输出低电平
    
    // 禁用所有未使用的弱上拉，只保留必要的
    WPUA = 0B00000001;           // 只为RA0启用弱上拉
    WPUB = 0x00;                 // 禁用所有PORTB的弱上拉
    IOCA = 0;                    // 禁用所有IO变化中断
    
    // 完全关闭ADC模块和所有模拟功能
    ADCON0 = 0;                  // 关闭ADC模块
    ADCON1 = 0;                  // 关闭ADC参考电压
    ANS2 = 0;                    // 禁用AN2模拟功能
    ANS10 = 0;                   // 禁用AN10模拟功能
    
    // 关闭PWM模块和所有定时器
    DisablePWM();                // 关闭LED PWM输出并设置IO为低电平
    DisableBoostPWM();           // 关闭升压PWM输出并设置IO为低电平
    PWMCON0 = 0;
    TMR2 = 0;                    // 清除Timer2计数器
    PR2 = 0;                     // 清除Timer2周期寄存器
    
    // 关闭所有未使用的外设
    PIE1 = 0;                    // 禁用所有外设中断
    PIR1 = 0;                    // 清除所有外设中断标志
    
    // 使用最低频率的内部振荡器
    OSCCON = 0x00;               // 使用31kHz内部低频振荡器(LFINTOSC)，关闭WDT
    
    // 配置中断唤醒
    PEIE = 0;                    // 禁用外设中断
    INTEDG = 0;                  // INT下降沿触发
    INTCON = 0x90;               // 只启用全局中断和INT外部中断
    INTF = 0;                    // 清除INT中断标志
    
    // 进入睡眠模式前清除WDT
    asm("clrwdt");
    asm("sleep");                // 进入睡眠模式
    
    // 唤醒后的处理
    asm("nop");
    asm("clrwdt");
    if(INTF) INTF = 0;
    
    if(long_press_timer >= LONG_PRESS_THRESHOLD) {
        g_sysmode = 1;
        long_press_timer = 0;
        g_night_timer = 0;
        timer_off = 0;
    }

    // 重新初始化系统
    Init_System();
    Init_ADC();
    Init_PWM();
    Init_Timer2();
}

// 白天低功耗模式，使用WDT定时唤醒检测光照条件
void DayLightSleepMode(void) {
    static uint8_t wdt_counter = 0;  // WDT唤醒计数器
    
    // 关闭ADC和PWM模块
    ADCON0 = 0;                  // 关闭ADC模块
    DisablePWM();                // 关闭LED PWM输出
    DisableBoostPWM();           // 关闭升压PWM输出
    T2CON = 0;                   // 关闭Timer2
    
    // 配置WDT为最长超时时间
    OPTION_REG = 0xCF;           // 设置预分频器分配给WDT，预分频率1:512 (最大值)
    
    // 保留必要的IO配置
    TRISA = 0B00000001;          // 只保留RA0为输入（按键）
    TRISB = 0B00000001;          // 保留RB0为输入（光敏电阻）
    PORTA = 0x00;                // 所有PORTA输出低电平
    PORTB = 0x00;                // 所有PORTB输出低电平
    
    // 配置弱上拉/下拉电阻
    WPUA = 0B00000001;           // 只为RA0启用弱上拉
    WPUB = 0B00000000;           // 禁用PORTB上拉
    
    // 关闭不必要的外设
    PIE1 = 0;                    // 禁用所有外设中断
    PIR1 = 0;                    // 清除所有外设中断标志
    
    // 使用低频振荡器以降低功耗
    OSCCON = 0x02;               // 使用31kHz内部低频振荡器(LFINTOSC)，启用WDT
    
    // 配置按键中断唤醒
    IOCA = 0B00000001;           // 允许RA0 IO电平变化中断
    RAIE = 1;                    // 允许PORTA端口中断
    INTCON = 0xC8;               // 开启全局中断和PORTA中断
    
    // 进入睡眠模式前清除WDT
    asm("clrwdt");
    asm("sleep");                // 进入睡眠模式
    
    // 唤醒后的处理（可能是WDT超时或按键中断）
    asm("nop");
    asm("clrwdt");
    
    // 检查是否是按键中断唤醒
    if(RAIF) {
        RAIF = 0;                // 清除PORTA中断标志
        wdt_counter = 0;         // 重置WDT计数器
        
        // 恢复系统状态
        OSCCON = 0x72;           // 恢复到16MHz
        __delay_ms(1);           // 等待时钟稳定
        
        // 重新初始化必要的模块
        Init_ADC();
        Init_Timer2();
        return;                  // 按键中断唤醒，直接返回
    }
    
    // WDT超时唤醒，增加计数器
    wdt_counter++;
    
    // 每8次WDT唤醒（约2秒）检测一次光照条件
    if(wdt_counter >= 8) {
        wdt_counter = 0;         // 重置WDT计数器
        
        // 恢复系统状态
        OSCCON = 0x72;           // 恢复到16MHz
        __delay_ms(1);           // 等待时钟稳定
        
        // 重新初始化必要的模块
        Init_ADC();
        
        // 检测光照条件
        ADC_Conver(SOLAR_CHANNEL, 7);
        __delay_ms(1);           // 等待ADC转换完成
        ADC_Conver(SOLAR_CHANNEL, 7); // 再次转换以确保结果准确
        
        // 如果检测到夜晚条件，切换到夜晚模式
        if(adresult <= SOLAR_LOW_THR) {
            g_night_mode = 1;           // 设置为夜晚模式
            g_night_timer = 0;          // 重置夜晚计时器
            timer_off = 0;              // 清除定时结束标志
            
            // 重新初始化PWM和Timer2
            Init_PWM();
            Init_Timer2();
            
            // 启用PWM输出并设置默认亮度
            EnablePWM();
            setLedPWM(DEFAULT_PWM);
            
            // 根据当前模式设置LED
            SetLedMode(g_mode);
            return;                     // 已切换到夜晚模式，返回
        }
        
        // 仍然是白天，重新初始化Timer2以继续检测
        Init_Timer2();
    }
    
    // 继续低功耗休眠
    return;
}

void main(void) {
    Init_System();
    Init_PWM();
    Init_BoostPWM();
    Init_ADC();
    Init_Timer2();

    // 初始化变量
    Add_Sign = 1;
    g_sysmode = 1;                                      // 默认开机
	g_mode = 1;
	bat_lvd_flag = 0;
    g_night_mode = 0;
	is_mode_switching = 0;
	timer_off = 0;
    
    // 初始检测电池电压和升压反馈电压
    adc_chk();
    boost_fb_chk();
	
	ReadEEPROM(EE_MODE_ADDR);
	uint16_t ee_temp = read_data;
	if(ee_temp == 0) {
		WriteEEPROM(EE_MODE_ADDR, 1);
		g_mode = 1;
	} else {
		g_mode = ee_temp;
		if(g_mode > 8) g_mode = 1;  // 确保模式值在1-8范围内
	}
    while (1) {
        asm("clrwdt");

		if(!g_sysmode) {                                // 唤醒失败继续休眠
			setLedPWM(0);
            DisablePWM();
			if(long_press_timer >= LONG_PRESS_THRESHOLD) {
                g_sysmode = 1;
                long_press_timer = 0;
				g_night_timer = 0;
				timer_off = 0;
            }
		} else {
            if(key_value == 0x84) {                     // 长按
                if(g_sysmode) {
				    g_sysmode = 0;                      // 关机,进入低功耗
                    Sleep_Mode();
                }
			    key_value = 0;
            } else if(key_value == 0x88) {              // 短按
                g_mode = (g_mode % 8) + 1;              // 支持8种模式循环
			    WriteEEPROM(EE_MODE_ADDR, g_mode);      // 写入按键更新
			    key_value = 0;
			    is_mode_switching = 1;
            }
			// else {                                    // 没有按键按下
            //    ReadEEPROM(EE_MODE_ADDR);               // 读取记忆状态
			//	g_mode = read_data;						// 更新到按键状态
            //}

			//*	bat_lvd_flag 有电0  低电1
			//*	g_night_mode 夜晚1	白天0
			//*	timer_off	 完成1	未完0
            
			if(!bat_lvd_flag && g_night_mode && !timer_off) {                             // 满电且夜晚
				if(is_mode_switching) {
					SWFlash(50, g_mode);
				} else {
					SetLedMode(g_mode);					// 设置亮灯
				}
            } else {
				setLedPWM(0);
                DisablePWM();
			}
        }
    }
}

void interrupt ISR() {
    if(INTF) {
		INTF = 0;                   // 清除中断
		long_press_timer = 0;
    }

    if(TMR2IF) {
        timer2_count++;                 // 1MS
        if(timer2_count == 4) {         // 4MS 检测按键
            get_keyvalue(&key_value);
        } else if(timer2_count >= 10) {
            timer2_count = 0;
            g_solar_check_timer++;
            if(g_night_mode && timer_off == 0) {
                g_night_timer++;    // 夜晚状态，增加延时计数
            }
			
			if(g_night_timer >= EIGHT_HOUR_TIME) {
				g_night_timer = 0;
				timer_off = 1;
			}

            Fast_Time++;                // 10MS
			// 防止Fast_Time溢出
            if(Fast_Time >= MAX_FAST_TIME) {
                Fast_Time = 0;
            }
			
			flash_Time++;
			msTime++;                    // 100ms计时器
			if(msTime >= 10) {
				msTime = 0;
				adc_chk();
				boost_fb_chk();  // 检测升压电路反馈电压并调整PWM
				cds_chk();
			}

            if(!RA0 && g_sysmode == 0) {
                long_press_timer++;
            } else {
                long_press_timer = 0;
            }
			
        }

        TMR2IF = 0;
    }
}

void handle_flash_combo(uint8_t count, uint16_t interval) {
    static uint8_t flash_count = 0;
    static uint16_t flash_timer = 0;
    static uint8_t flash_state = 0; // 0: flashing, 1: pause
    
    flash_timer++;
    
    if (flash_state) { // 暂停状态
        DisablePWM();
        if (flash_timer >= 100) { // 1秒暂停
            flash_state = 0;
            flash_timer = 0;
        }
        return;
    }
    
    // 闪烁状态
    flashLED(interval);
    if (!LEDstatus && flash_count < count) {
        flash_count++;
    } else if (flash_count >= count) {
        flash_count = 0;
        flash_state = 1;
        flash_timer = 0;
    }
}

// 全局变量用于handle_auto_cycle_mode函数
static uint8_t auto_mode = 2; // 从模式2开始循环
static uint16_t auto_timer = 0;
static uint8_t combo_state_for_auto = 0;
static uint16_t combo_timer_for_auto = 0;

void handle_auto_cycle_mode(void) {
    auto_timer++;
    
    // 每30秒切换一次模式
    if (auto_timer >= 3000) {
        auto_timer = 0;
        if (++auto_mode > 7) auto_mode = 2;
    }
    
    // 调用对应模式的处理函数
    switch (auto_mode) {
        case 3: handle_flash_mode(FAST_BLINK_MS); break;
        case 4: handle_flash_mode(SLOW_BLINK_MS); break;
        case 5: handle_flash_combo(3, 100); break;
        case 6: handle_flash_combo(3, 1000); break;
        case 7: handle_combo_mode(&combo_state_for_auto, &combo_timer_for_auto, 3); break;
        default: handle_breath_mode(); // 包括case 2和其他情况
    }
}