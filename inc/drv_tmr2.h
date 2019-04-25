/* 
 * File:   drv_tmr2.h
 * Author: niumiaomiao
 *
 * Created on 2019年4月9日, 下午3:36
 */

#ifndef DRV_TMR2_H
#define	DRV_TMR2_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic.h>
    
    typedef void (*TMR2_InterruptHandler_t)();
    extern void tmr2_init();
    extern void tmr2_start();
    extern void tmr2_stop();
    extern void tmr2_isr_enable();
    extern void tmr2_isr_disable();
    extern void tmr2_isr();
    extern void tmr2_set_handler(TMR2_InterruptHandler_t handler);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_TMR2_H */

