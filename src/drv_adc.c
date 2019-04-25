#include "../inc/drv_adc.h"

void adc_init() {
    //设置模拟通道  RA4---AN3
    ADCON0bits.CHS = 0x03;
    //是能ADC转换
    ADCON0bits.ADON = 1;
    //设置ADC格式  右对齐
    ADCON1bits.ADFM = 1;
    //选择时钟
    ADCON1bits.ADCS = 0x02;
    //使能电压配置位  参考电压VDD
    ADCON1bits.ADPREF = 0x00;   
}

unsigned int getADC() {
    ADCON0bits.GO_nDONE = 1;
    while(!PIR1bits.ADIF);
    PIR1bits.ADIF = 0;
    return (ADRES & 0x3FF);
}
