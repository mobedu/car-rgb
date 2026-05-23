/*
					   SOP-8
*			VDD	1	-|		|-	8 GND
*			CDS	2	-|		|-	7 KEY/RA0/AN0
*		LED_PWM	3	-|		|-	6 POWER FB/RA1
*	AN10/BAT	4	-|		|-	5 POWER PWM/RA2/AN2
*/

/*
		*			CDS ADC对应值
		*	0.5V		0x00A8
		*	1.64v		0x022F
		*
		*			BAT ADC对应值
		*	2.66V		0x0800
		*	2.99V		0x080F
		*	3.01V		0x0940
		*	3.47V		0x0953
		*	3.5V		0x0960
		*	3.87V		0x0A60
		*	3.9V		0x0A80
		*	4.0V		0x0D01
*/

#ifndef   _CONFIG_H_
#define   _CONFIG_H_

#pragma	warning	disable 752
#pragma	warning	disable 373			// 禁用多余的警告

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000			// 16MHz,使用内部晶振时必须定义此频率
								// 如果FCPU_DIV选择2T，则此时钟值减半
#endif

#define     POWER_RATIO  	(4096UL*1.2*1000)

#define _DEBUG						// 调试程序

#define	uint8_t     unsigned char
#define	uint16_t    unsigned short
#define	int16_t     signed short
#define	uint32_t	unsigned long

// 引脚定义
#define LED_PIN         RB1     // LED输出引脚 
#define BUTTON_PIN      RA0     // 按键输入引脚
#define PowerPWM_PIN    RA2     // 功率PWM输出引脚
#define BATT_CHANNEL    10      // 电池电压监测ADC通道 AN10
#define SOLAR_CHANNEL   8       // 太阳能板电压监测ADC通道 AN8
#define PowerFB_CHANNEL 1		// 电压反馈引脚

// EEPROM地址设置
#define EE_MODE_ADDR    0x7A    // 模式存储地址

// 时间常量定义
#define FAST_BLINK_MS           30			// 快闪间隔时间(ms)
#define SLOW_BLINK_MS           100			// 慢闪间隔时间(ms)
#define BREATH_STEP_MS          1			// 呼吸效果步进时间(ms)

// PWM 设置
#define PWM_PERIOD              999        // PWM周期值

/* 电池电压阈值宏定义 */
#define BATTERY_4V      0xD01
#define BATTERY_3_7V    0xC80
#define BATTERY_3_5V    0xBFE
#define BATTERY_3_3V    0xB80

// 其他常量
#define MAX_FAST_TIME 200			// 快速计时器最大值
#define EIGHT_HOUR_TIME 2880000		// 8小时定时 8 * 3600 *100=2880000  1分钟:5*60*100=30000
#define LONG_PRESS_THRESHOLD 270	// 长按时间阈值

#endif