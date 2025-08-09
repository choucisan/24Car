#include "Exti.h"


void Exti_Init(void)
{
      NVIC_EnableIRQ(GPIOB_INT_IRQn);	
}



void GROUP1_IRQHandler(void)
{
    uint32_t Exti_Flag = DL_GPIO_getEnabledInterruptStatus(GPIOB, DL_GPIO_PIN_21);//¼ì²âÖÐ¶Ï¹ÒÆð
    if (Exti_Flag & KEY1)
    {
		LED_togglePins;
        DL_GPIO_clearInterruptStatus(GPIOB, DL_GPIO_PIN_21);
    }
}













