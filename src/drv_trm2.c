 #include "../inc/drv_tmr2.h"

TMR2_InterruptHandler_t tmr2_isr_handler;

void tmr2_init() {
    //配置T2CON寄存器
    T2CONbits.T2OUTPS = 0x0F;       //后分频   16
    T2CONbits.T2CKPS = 0x01;        //预分频   4
    //设置tmr2周期
    PR2 = 249;
}
//使能tmr2
void tmr2_start() {
    T2CONbits.TMR2ON = 1;
}
//禁止tmr2
void tmr2_stop() {
    T2CONbits.TMR2ON = 0;
}
//使能tmr2中断
void tmr2_isr_enable() {
    PIE1bits.TMR2IE = 1;
}
//禁止tmr2中断
void tmr2_isr_disable() {
    PIE1bits.TMR2IE = 0;
}
//tmr2中断
void tmr2_isr() {
    PIR1bits.TMR2IF = 0;
    if(tmr2_isr_handler) {
        tmr2_isr_handler();
    }
}
//设置中断服务函数
void tmr2_set_handler(TMR2_InterruptHandler_t handler) {
    tmr2_isr_handler = handler;
}