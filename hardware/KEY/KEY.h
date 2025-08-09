#ifndef __KEY_H_
#define __KEY_H_

#include "A_include.h"

#define KEY0					((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_21)==DL_GPIO_PIN_21) ? 1:0)
#define KEY1					((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_23)==DL_GPIO_PIN_23) ? 1:0)
#define KEY2					((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_24)==DL_GPIO_PIN_24) ? 1:0)
#define KEY3					((DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_18)==DL_GPIO_PIN_18) ? 1:0)

typedef enum{
    key_release,
    key_press,
    key_wait,
}Key_state;

extern uint8_t Key0_Flag,//按键标志 随用随清除
Key1_Flag;

void KEY_Init(void);
void Key_Scan(void);
void key_scan(void);
#endif

