#ifndef _A_include_H_
#define _A_include_H_

/******************ϵͳͷ�ļ�*******************/
#include "ti_msp_dl_config.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "math.h"

/******************�û��ļ�*******************/
#include "A_include.h"


/******************software*******************/
#include "..\software\delay\delay.h"
#include "..\software\Timer\Timer.h"
#include "..\software\uart\uart.h"




/******************HARDWARE*******************/
#include "..\HARDWARE\LED\LED.h"
#include "..\HARDWARE\key\key.h"
#include "..\HARDWARE\OLED\OLED.h"
#include "..\HARDWARE\Exti\Exti.h"
#include "..\HARDWARE\Motor\Motor.h"
#include "..\HARDWARE\Encoder\Encoder.h"



#include "HC_SR04.h"
#include "Angle_PID.h"
#include "MPU.h"
void xun_ji(void);
extern uint8_t aa, enter_flag, ab, ac, mode2_Flag, nu;
extern int tt;
float MPU_change(float zhi);
extern uint8_t flag3,mode3_Flag;
extern float my1_Yaw;
extern uint8_t flag3, mode3_Flag,flag1, flg3_num,delay_flag;
void xun_ji1(void);

extern int16_t Encoder_Count,Encoder1_Count,sp1,sp2,length;
extern uint16_t beep_cnt,beep_flag;
void BEEP(void);
extern uint16_t xx_delay;



//extern atk_ms901m_attitude_data_t attitude_dat;           /* ��̬������ */
extern  float YAW_out;

extern uint8_t mode_flag,Enter_flag;

extern uint32_t stateChangeTimer; // ״̬�仯��ʱ��
extern uint32_t Length,xie_length1,xie_length2;
extern volatile uint32_t msHcCount; // ms����
extern int speed_l,speed_r;
#endif
