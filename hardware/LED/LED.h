#ifndef __LED_H_
#define __LED_H_


#include "A_include.h"

#define LEDS(x)      ( (x) ? (DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_0)) : (DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_0)) )

#define LEDR(x)      ( (x) ? (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_26)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_26)) )
#define LEDG(x)      ( (x) ? (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_27)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_27)) )
#define LEDB(x)      ( (x) ? (DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_22)) : (DL_GPIO_clearPins(GPIOB,DL_GPIO_PIN_22)) )

#define LED_togglePins      DL_GPIO_togglePins(GPIOB,DL_GPIO_PIN_27);//IOµçÆ½·­×ª

void LED_Test(void);

#endif

