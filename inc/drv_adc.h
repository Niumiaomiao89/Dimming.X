/* 
 * File:   drv_adc.h
 * Author: niumiaomiao
 *
 * Created on 2019年4月8日, 下午8:06
 */

#ifndef DRV_ADC_H
#define	DRV_ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <pic.h>

    extern void adc_init();
    extern unsigned int getADC();

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_ADC_H */

