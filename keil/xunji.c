#include "Xunji.h"

uint8_t De_Num1,De_Num2,De_Num3,De_Num4,De_Num5;

//#define L2 ((DL_GPIO_readPins(GPIOA,DL_GPIO_PIN_8)==DL_GPIO_PIN_8) ? 1:0)
//#define L1 DL_GPIO_readPins(GPIOB,DL_GPIO_Pin_4)
//#define M0 DL_GPIO_readPins(GPIOB,DL_GPIO_Pin_12)
//#define R1 DL_GPIO_readPins(GPIOB,DL_GPIO_Pin_9)
//#define R2 DL_GPIO_readPins(GPIOB,DL_GPIO_Pin_2)
void Detect_Num(void)
{
//                    OLED_ShowNum(0,2*16,((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_13)==DL_GPIO_PIN_13) ? 1:0),4,OLED_8X16);
//        OLED_ShowNum(0,3*16,((DL_GPIO_readPins(GPIOB,DL_GPIO_PIN_20)==DL_GPIO_PIN_20) ? 1:0),4,OLED_8X16);
    
    if (L2) De_Num1 = 1;
    else De_Num1 = 0;
    if (L1) De_Num2 = 1;
    else De_Num2 = 0;
    if (M0) De_Num3 = 1;
    else De_Num3 = 0;
    if (R1) De_Num4 = 1;
    else De_Num4 = 0;
    if (R2) De_Num5 = 1;
    else De_Num5 = 0;
}
uint8_t read_irs_state( void )
{
    int i;
    uint8_t status  = 0;
    uint8_t state[5];
 
    state[0]  = L2;
    state[1]  = L1;
    state[2]  = M0;
    state[3]  = R1;
    state[4]  = R2;
    for( i = 0; i < 5; i++ ) {
        status |=( state[i] << i );
    }
    return status;
}

uint8_t get_middle_filter_irs_state( void )
{
    int i;
    uint8_t state[9];
 
    for( i =0; i<9; i++ ) {
        state[i] = read_irs_state();
    }
    return state[4];
 
}
//1.异常情况，小车向需要右偏（左轮速度增加，右轮减少）
//case 0x19: cur_error = 2; break;   //B11001
//case 0x1d: cur_error = 4; break;   //B11101
//case 0x1c: cur_error = 6; break;   //B11100
//case 0x18: cur_error = 7; break;   //B11000
//case 0x1e: cur_error = 8; break;   //B11110
// 
//2.正常情况
//case 0x0 :                          //B00000
//case 0x1b: cur_error = 0;  break;   //B11011
// 
//3.异常情况，小车向需要左偏（右轮速度增加，左轮减少）
//case 0x13: cur_error = -2;  break;   //B10011
//case 0x17: cur_error = -3;  break;   //B10111
//case 0x3 : cur_error = -4;  break;   //B00111
//case 0x7 :                           //B00111
//case 0x1 : cur_error = -7;  break;   //B00001
//case 0xf : cur_error = -8;  break;   //B01111
// 
//4.极端情况，小车已经冲出赛道，根据冲出之前的误差，将误差调整到最大
//case 0x1f: cur_error = pid.error > 0 ? 9 : -9; break;//B11111
uint8_t cur_error = 0;
void Turn_PID(void)
{
    switch (read_irs_state())
    {
		case 0x01: PWM_SET(200,2400); break;
		case 0x03: PWM_SET(300,2000); break;
		case 0x02: PWM_SET(500,1500); break;
		case 0x06: PWM_SET(600,1000); break;
		case 0x04: PWM_SET(700,700); break;
		case 0x0c: PWM_SET(1000,600); break;
		case 0x08: PWM_SET(1500,500); break;
		case 0x18: PWM_SET(2000,300); break;
		case 0x10: PWM_SET(2400,200); break;
    }

}