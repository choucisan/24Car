#include "Motor.h"



void Motor_Init(void)
{
  DL_Timer_startCounter(Motor_INST);
}


void PWM_SET(int duty0,int duty1)
{
	duty0=duty0>2700?2700:(duty0<-2700?(-2700):duty0); 
    duty1=duty1>2700?2700:(duty1<-2700?(-2700):duty1);
	if (duty0 <0 )
	{
		duty0 = 0;
	}
	if (duty1 < 0)
	{
		duty1 = 0;
	}
        // ��ת�߼�
        DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_26);
        DL_GPIO_clearPins(GPIOA,DL_GPIO_PIN_27);
        DL_Timer_setCaptureCompareValue(Motor_INST, duty1, DL_TIMER_CC_0_INDEX);
//        DL_Timer_setCaptureCompareValue(Motor_INST, duty0, DL_TIMER_CC_2_INDEX);
        // ����PWMռ�ձȣ�������Ҫ����ʵ�ʵ�PWM����������
		// ��ת�߼�
        DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_5);
        DL_GPIO_setPins(GPIOA,DL_GPIO_PIN_4);
//		 DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_10);
//        DL_GPIO_setPins(GPIOB,DL_GPIO_PIN_11);
//        duty1 = duty1 *1;
        DL_Timer_setCaptureCompareValue(Motor_INST, duty0, DL_TIMER_CC_1_INDEX);
//        DL_Timer_setCaptureCompareValue(Motor_INST, duty1, DL_TIMER_CC_3_INDEX);
        // ����PWMռ�ձȣ�������Ҫ����ʵ�ʵ�PWM����������
}


