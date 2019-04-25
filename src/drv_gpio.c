#include "../inc/drv_gpio.h"

void gpio_init() {
    //PORTA
    //RA4设置为模拟输入
    TRISAbits.TRISA4 = 1;
    ANSELAbits.ANSA4 = 1;
    LATAbits.LATA4 = 0;
    //RA2设置为数字输出
    TRISAbits.TRISA2 = 0;
    ANSELAbits.ANSA2 = 0;
    LATAbits.LATA2 = 1;
}