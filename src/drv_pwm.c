#include "../inc/drv_pwm.h"

void pwm_init() {
    //使能PWM输出引脚
    PWM3CONbits.OE = 1;
    //PWM高电平有效
    PWM3CONbits.POL = 0;
    //使能标准PWM模式
    PWM3CONbits.MODE = 0x00;
    //PWM中断允许
    PWM3INTE = 0x00;
    //PWM中断请求
    PWM3INTF = 0x00;
    //PWM时钟选择位
    PWM3CLKCONbits.PS = 0x00;
    PWM3CLKCONbits.CS = 0x00;
    //PWM重装载出发寄存器
    PWM3LDCONbits.LDA = 1;          //在当前周期结束时装载 OF、PH、DC和PR缓冲器
    //偏移触发源选择寄存器
    PWM3OFCONbits.OFM = 0x00;       //独立运行模式
    //设置相位计数器
    PWM3PH = 0x00;
    //设置占空比
    PWM3DC = 0x00;
    //设置PWM周期
    PWM3PR = 0x270F;
    //设置偏移计数器
    PWM3OF = 0x00;
    //设置定时器计数器
    PWM3TMR = 0x00;
    //使能PWM
    PWM3CONbits.EN = 1;
}

void pwm_dutyCycle_set(uint16_t duty) {
    PWM3DC = duty;
}

void pwm_loadBuffer_set() {
    PWM3LDCONbits.LDA = 1;
}
