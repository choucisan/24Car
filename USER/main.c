#include "A_include.h"
#include "Angle_PID.h"
#include "xunji.h"
#include "Encoder.h"
#include "ti_msp_dl_config.h"




void BEEP(void);

//void Get_Angle(uint8_t way);
#define Pi 3.14159265
uint8_t Way_Angle=2;                             //��ȡ�Ƕȵ��㷨��1����Ԫ��  2��������  3�������˲� 
float Angle_Balance,Gyro_Balance,Gyro_Turn; //ƽ����� ƽ�������� ת��������
float Acceleration_Z;  
uint8_t aa = 0, enter_flag = 0, mode2_Flag, ab;
uint8_t stop_flag = 0, nu;
float my1_Yaw;
uint8_t flag3, mode3_Flag = 0,flag1, flg3_num = 0, delay_flag, cishu;
uint8_t over, uu, i;


uint8_t mode_flag = 0,Enter_flag = 0;
float YAW_out;
float Last_YAW_out;
float yaw_arr[10];
/**************oled****************/
void Oled_Show(void)
{
//	key_scan();
	key_scan();
	OLED_ShowString(50, 0, "M:", OLED_8X16);
	OLED_ShowNum(70,0,mode_flag, 1, OLED_8X16);
	OLED_ShowString(80, 0, "E:", OLED_8X16);
	OLED_ShowNum(100,0,enter_flag, 1, OLED_8X16);
//	OLED_ShowSignedNum(90,40,Speed_PID(speed_l, speed_r), 4, OLED_8X16);//stateChangeTimerstateChangeTimer Length
	OLED_ShowSignedNum(90,40,Length, 4, OLED_8X16);
//	OLED_ShowNum(90,48,xie_length1, 4, OLED_8X16);
	OLED_ShowSignedNum(40,40,stateChangeCount, 2, OLED_8X16);
	
//	OLED_ShowFloatNum(20,20,speed_l, 3, 1, OLED_8X16);//YAW_out
//	OLED_ShowFloatNum(80,20,speed_r, 3, 1, OLED_8X16);//Last_YAW_out
	OLED_ShowFloatNum(20,20,YAW_out, 3, 1, OLED_8X16);//YAW_out
	OLED_ShowFloatNum(80,20,Last_YAW_out, 3, 1, OLED_8X16);//Last_YAW_out
	OLED_ShowNum(20,40,stateChangeCount,1,OLED_8X16);

	OLED_ShowNum(0,0,L2, 1, OLED_8X16);
	OLED_ShowNum(8,0,L1, 1, OLED_8X16);
	OLED_ShowNum(16,0,M0, 1, OLED_8X16);
	OLED_ShowNum(24,0,R1, 1, OLED_8X16);
	OLED_ShowNum(32,0,R2, 1, OLED_8X16);
	OLED_Update(); 
}
/**************SR04_test****************/

void SR_04_demo(void)
{
	
}
#define X ((DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_22)==DL_GPIO_PIN_22) ? 1:0)
#define TIMER_2_INST                                                     (TIMG0)
#define TIMER_2_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_2_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_2_INST_LOAD_VALUE                                          (6399U)



int main(void)
{
	SYSCFG_DL_init(); //оƬ��Դ��ʼ��,��SysConfig���������Զ�����
//	DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_12);

	KEY_Init();
	Motor_Init();
	OLED_Init(); 
//	delay_ms(500);
	PWM_SET(0,0);
	Timer_Init();  
	//UART_Init();
	Encoder_Init();
	key_scan();
	jy61pInit();
	mode_flag = 0;
	enter_flag = 0;
	DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_12);


	while(1)
	{
//		imu_demo();
		Oled_Show();
		YAW_out = get_angle();
		judge_way();

		if(beep_cnt > 0) DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_12);
		else DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_12);
	}
}
uint16_t beep_cnt,beep_flag;

void BEEP(void)
{
	beep_cnt = 50;

}