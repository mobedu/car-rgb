#ifndef VOLT_H_
#define VOLT_H_

// 电池电压检测，参考电压标准为3V，低保护电压为2.66V，恢复电压为2.99V，上部电阻为470K，下部电阻为470K。
// 低保护电压ADC值=(470/940）* 2.66 / 2.4V * 4096 = 2269;       0x8DD
// 恢复电压ADC值=(470/940）* 2.99 / 2.4V * 4096 = 2551;       0x97F
// 3.9V     PWM:100%    1023    2663    0xA67
// 3.5V     PWM:70%     716     2391    0x957
// <3.5V    PWM:50%     511 
#define adc_bat_39      0xD01    // 3.9V（参考电压为2.4V)
#define adc_bat_35      0xBFE    // 3.5V（参考电压为2.4V)
#define adc_bat_wake    0xA0F    // 唤醒电压2.99V(参考电压为2.4V)
#define adc_bat_min     0x8FF    // 低保护电压2.66V（参考电压为2.4V)

//太阳能板电压检测，参考电压标准为3V，夜晚阈值电压为0.75V，白天阈值电压为1.65V，上部电阻为30K，下部电阻为10K。
// ADC值 = (下电阻/(上+下电阻)) * 输入电压  / 参考电压 * 4095
//夜晚阈值电压ADC值=(10/40）* 0.75 / 3v * 4095 = 256;       0x100
//白天阈值电压ADC值=(10/40）* 1.65 / 3v * 4095 = 563;       0x233
#define SOLAR_HIGH_THR  0x233       // 1.65V AD value
#define SOLAR_LOW_THR   0x100       // 0.75V AD value

#define DEFAULT_PWM 860             // 默认PWM占空比86%
#define END_PWM     600             // 最低PWM占空比60%

// 串联电阻180K， 并联电阻10K
// 升压电路目标电压对应的ADC值
#define TARGET_VOLTAGE 0x800         // 升压电路目标电压对应的ADC值


void Init_ADC(void);
uint8_t ADC_Conver(uint8_t adch, uint8_t adldo);
void adc_chk(void);
void boost_fb_chk(void);
void cds_chk(void);

#endif