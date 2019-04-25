/* 
 * File:   drv_pwm.h
 * Author: niumiaomiao
 *
 * Created on 2019年4月8日, 下午8:23
 */

#ifndef DRV_PWM_H
#define	DRV_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic.h>
#include <stdint.h>
#include <stdbool.h>
    
    extern void pwm_init();
    extern void pwm_dutyCycle_set(uint16_t duty);
    extern void pwm_loadBuffer_set();
    
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_PWM_H */

