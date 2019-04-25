#include "../inc/drv_osc.h"

void osc_init() {
    //禁止4xPLL
    OSCCONbits.SPLLEN = 0x00;
    //使能16MHz晶振
    OSCCONbits.IRCF = 0x0F;
    //选择振荡器
    OSCCONbits.SCS = 0x00;
    //振荡器模块以出厂时校准的频率运行
    OSCTUNEbits.TUN = 0x00;
    //等待内部高速振荡器稳定
    while(!OSCSTATbits.HFIOFR);
}
