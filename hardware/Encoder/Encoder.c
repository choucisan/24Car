#include "Encoder.h"
#define Encoder_PORT                                                     (GPIOA)

/* Defines for A: GPIOA.14 with pinCMx 36 on package pin 7 */
// pins affected by this interrupt request:["A","B","EA1","EB1"]
#define Encoder_INT_IRQN                                        (GPIOA_INT_IRQn)
#define Encoder_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define Encoder_A_IIDX                                      (DL_GPIO_IIDX_DIO14)
#define Encoder_A_PIN                                           (DL_GPIO_PIN_14)
#define Encoder_A_IOMUX                                          (IOMUX_PINCM36)
/* Defines for B: GPIOA.13 with pinCMx 35 on package pin 6 */
#define Encoder_B_IIDX                                      (DL_GPIO_IIDX_DIO13)
#define Encoder_B_PIN                                           (DL_GPIO_PIN_13)
#define Encoder_B_IOMUX                                          (IOMUX_PINCM35)
/* Defines for EA1: GPIOA.15 with pinCMx 37 on package pin 8 */
#define Encoder_EA1_IIDX                                    (DL_GPIO_IIDX_DIO15)
#define Encoder_EA1_PIN                                         (DL_GPIO_PIN_15)
#define Encoder_EA1_IOMUX                                        (IOMUX_PINCM37)
/* Defines for EB1: GPIOA.17 with pinCMx 39 on package pin 10 */
#define Encoder_EB1_IIDX                                    (DL_GPIO_IIDX_DIO17)
#define Encoder_EB1_PIN                                         (DL_GPIO_PIN_17)
#define Encoder_EB1_IOMUX                                        (IOMUX_PINCM39)
int16_t Encoder_Count,Encoder1_Count,sp1,sp2,length;

void Encoder_Init(void)
{
    NVIC_EnableIRQ(Encoder_INT_IRQN);
}

int16_t Encoder_Get(void)
{
	int16_t Temp1;
	Temp1 = Encoder_Count;
	Encoder_Count = 0;
	return Temp1;
}
int16_t Encoder1_Get(void)
{
	int16_t Temp2;
	Temp2 = Encoder1_Count;
	Encoder1_Count = 0;
	return Temp2;
}
//该中断函数与按键中断冲突   屏蔽一方即可
void GROUP1_IRQHandler(void)
{
  uint8_t Encodeg_flag,A_flag,B_flag,direction_flag;
	uint8_t Encodeg1_flag,A1_flag,B1_flag,direction1_flag;
	static uint16_t count;
	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
	{
		case Encoder_INT_IIDX:
		if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_A_PIN))
		{
            Encodeg_flag = 1;//A中断
            if(DL_GPIO_readPins(GPIOA, Encoder_A_PIN)) A_flag = 1;
            else A_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_B_PIN)) B_flag = 1;
            else B_flag = 0;
            direction_flag = A_flag+B_flag+Encodeg_flag;//求和判断转动方向，偶数正转，奇数反转
            if(direction_flag == 0 || direction_flag ==2)Encoder_Count++;
            else Encoder_Count--;
            
			DL_GPIO_clearInterruptStatus(GPIOA, Encoder_A_PIN);
		}
		
		if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_B_PIN))
		{			
			Encodeg_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_A_PIN)) A_flag = 1;
            else A_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_B_PIN)) B_flag = 1;
            else B_flag = 0;
            direction_flag = A_flag+B_flag+Encodeg_flag;
            if(direction_flag == 0 || direction_flag ==2)Encoder_Count++;
            else Encoder_Count--;
            
			DL_GPIO_clearInterruptStatus(GPIOA, Encoder_B_PIN);
		}
		if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_EA1_PIN))
		{
             Encodeg1_flag = 1;//A中断
            if(DL_GPIO_readPins(GPIOA, Encoder_EA1_PIN)) A1_flag = 1;
            else A1_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_EB1_PIN)) B1_flag = 1;
            else B1_flag = 0;
            direction1_flag = A1_flag+B1_flag+Encodeg1_flag;//求和判断转动方向，偶数正转，奇数反转
            if(direction1_flag == 0 || direction1_flag ==2)Encoder1_Count++;
            else Encoder1_Count--;
            
			DL_GPIO_clearInterruptStatus(GPIOA, Encoder_EA1_PIN);
            			
		}
		if(DL_GPIO_getEnabledInterruptStatus(GPIOA, Encoder_EB1_PIN))
		{
            Encodeg1_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_EA1_PIN)) A1_flag = 1;
            else A1_flag = 0;
            if(DL_GPIO_readPins(GPIOA, Encoder_EB1_PIN)) B1_flag = 1;
            else B1_flag = 0;
            direction1_flag = A1_flag+B1_flag+Encodeg1_flag;
            if(direction1_flag == 0 || direction1_flag ==2)Encoder1_Count++;
            else Encoder1_Count--;
            
			DL_GPIO_clearInterruptStatus(GPIOA, Encoder_EB1_PIN);		
		}
		break;
	}
	if (++count == 77)
	{
		sp1 = -Encoder_Get();
		sp2 = -Encoder1_Get();
		length = (sp1 + sp2)/2 + length;
		count = 0;
	}
}
