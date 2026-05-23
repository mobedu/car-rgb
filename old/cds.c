#include <sc.h>
#include "config.h"
#include "cds.h"

unsigned char cds_auto_mode = 1;

void cds_adc_init(void) {
    // 配置 AN10 (RB2) 用于光敏检测
    ANSEL1 |= (1 << 2);
    TRISB |= (1 << 2);
}

unsigned int cds_read_adc(void) {
    unsigned int adc;
    // 设置 AN10
    ADCON0 = (ADCON0 & 0xC3) | (10 << 2);
    ADCON0 |= 0x02;
    while (ADCON0 & 0x02) asm("clrwdt");
    adc = (ADRESH << 8) | ADRESL;
    return adc;
}

void cds_update(void) {
    if (!cds_auto_mode) return;
    unsigned int adc = cds_read_adc();
    if (adc > CDS_BRIGHT_THRESH) {
        // 环境亮，关闭LED
        extern unsigned char power_state;
        power_state = 0;
    }
}