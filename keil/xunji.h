#ifndef __XUNJI_H_
#define __XUNJI_H_


#define R2 ((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_18)==DL_GPIO_PIN_18) ? 1:0)
#define R1 ((DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_3)==DL_GPIO_PIN_3) ? 1:0) 
#define M0 ((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_4)==DL_GPIO_PIN_4) ? 1:0)  
#define L1  ((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_3)==DL_GPIO_PIN_3) ? 1:0) 
#define L2 ((DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_6)==DL_GPIO_PIN_6) ? 1:0)  


#include "A_include.h"

extern uint8_t De_Num1,De_Num2,De_Num3,De_Num4,De_Num5;
void Detect_Num(void);
void Turn_PID(void);
uint8_t read_irs_state( void );
uint8_t get_middle_filter_irs_state( void );

#endif