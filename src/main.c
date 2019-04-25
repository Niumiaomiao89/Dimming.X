/*
 * File:   main.c
 * Author: niumiaomiao
 *
 * Created on 2019年4月8日, 下午6:13
 */

// CONFIG1
#pragma config FOSC = INTOSC    //  (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = ON        // Watchdog Timer Enable (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOREN = OFF    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "../inc/drv_osc.h"
#include "../inc/drv_gpio.h"
#include "../inc/drv_pwm.h"
#include "../inc/drv_adc.h"
#include "../inc/drv_tmr2.h"

#define global_interrupt_enable()       INTCONbits.GIE = 1
#define global_interrupt_disable()      INTCONbits.GIE = 0
#define peripheral_interrupt_enable()   INTCONbits.PEIE = 1
#define peripheral_interrupt_disable()  INTCONbits.PEIE = 0

#define _XTAL_FREQ                      16000000

#define ADC_MAX_VALUE                   1010
#define ADC_PERIOD_VALUE                10
#define PWM_VALUE_MAX                   10000
#define PWM_VALUE_MIN                   0
#define STEP                            10

#define COUNT                           10

volatile bool on;
//ADC采集值
volatile uint16_t adc_gather_value;
//ADC滤波值
volatile uint16_t adc_filter_value;
//PWM占空比目标值
volatile uint16_t target_value = 0;
//PWM占空比当前值
volatile uint16_t current_value = 0;

//ADC采集
void adc_gather() {
    uint8_t i,j;
    uint16_t temp,sum = 0;
    uint16_t value_buf[COUNT] = {0};
    for(i = 0; i < COUNT; i++) {
        value_buf[i] = getADC();
        __delay_ms(5);
    }
    for(j = 0; j < COUNT - 1; j++) {
        for(i = 0;i < COUNT - j; i++) {
            if(value_buf[i] > value_buf[i + 1]) {
                temp = value_buf[i];   
                value_buf[i] = value_buf[i + 1];
                value_buf[i + 1] = temp;
            }
        }
    }
    for(i = 1; i < COUNT - 1; i++) {
        sum += value_buf[i];
    }
    adc_gather_value = sum / (COUNT - 2);
}
//ADC滤波     
void adc_filter() {
    uint16_t sum = 0;
    static uint8_t index = 0;
    static uint16_t value_buf[COUNT] = {0};
    if(index >= COUNT) {
            index = 0;
        }
    value_buf[index++] = adc_gather_value;
    for(unsigned int i = 0; i < COUNT; i++) {
        sum += value_buf[i];
    }
    adc_filter_value = sum / COUNT;
}
//更新开关状态
void led_update_state() {
    static uint8_t cnt_on = 0;
    static uint8_t cnt_off = 0;
    if(on) {
        if(adc_filter_value < 20) {
            cnt_off++;
            if(cnt_off >= 30) {
                cnt_off = 0;
                on = false;
            }
        } else {
            cnt_off = 0;
        }
    } else {
        if(adc_filter_value > 20) {
            cnt_on++;
            if(cnt_on >= 30) {
                cnt_on = 0;
                on = true;
            }
        } else {
            cnt_on = 0;
        }
    }
}
//更新PWM占空比
void pwm_update_duty() {
    if(on) {
        if(adc_filter_value > ADC_MAX_VALUE) {
            target_value  = PWM_VALUE_MAX;
        } else {
            target_value = (adc_filter_value - ADC_PERIOD_VALUE) * 10;
        }
    } else {
        target_value = PWM_VALUE_MIN;
    }
}
//执行PWM
void pwm_run() {
    if(current_value + STEP < target_value) {
        current_value += STEP;
    } else if (current_value > target_value + STEP) {
        current_value -= STEP;
    } else {
        current_value = target_value;
    }
    pwm_dutyCycle_set(current_value);
    pwm_loadBuffer_set();
} 
//中断初始化
void set_interrupt_handle() {
    tmr2_set_handler(pwm_run);
}
//主函数
void main(void) {
    //使能全局中断
    global_interrupt_enable();
    //使能外设中断
    peripheral_interrupt_enable();
    //初始化中断服务函数
    set_interrupt_handle();
    //振荡器初始化
    osc_init();
    //管脚初始化
    gpio_init();
    //TMR2初始化
    tmr2_init();
    tmr2_start();
    tmr2_isr_enable();
    //PWM初始化
    pwm_init();
     //ADC初始化
    adc_init();

    while(1) {
        //看门狗
        CLRWDT();
        //ADC采集
        adc_gather();
        //ADC滤波
        adc_filter();
        //更新LED开关状态
        led_update_state();
        //更新PWM占空比
        pwm_update_duty();
    }
}
//中断服务函数
void interrupt ISR() {
    if(PIE1bits.TMR2IE && PIR1bits.TMR2IF) {
        tmr2_isr();
    }
}
