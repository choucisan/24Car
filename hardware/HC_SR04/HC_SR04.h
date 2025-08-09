#ifndef _HCSR_H
#define _HCSR_H



#define TRIG_1_High()  DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_19)
#define TRIG_1_Low()   DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_19)
#define ECHO_1_Low     DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_20) == 0
#define ECHO_1_High    DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_20) != 0

void Delay_us(uint16_t xus);
double HC_Length(void);	

#endif

