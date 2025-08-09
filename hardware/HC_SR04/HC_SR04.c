#include "A_include.h"
#include "HC_SR04.h"

double  Length_1;
double  Length_2;

uint16_t t1, t2;
uint16_t t3 = 0;

double HC_Length(void)	
{
		TRIG_1_High();
		delay_ms(10);
		TRIG_1_Low();	
		/*��һ��ʱ�䣬������ʱ��㲻�ٵȴ�����ֹwhile����*/
		while(ECHO_1_Low && (t3++ < 15000));
		t1 = DL_TimerG_getTimerCount(TIMER_0_INST);
		t3 = 0;
		while(ECHO_1_High && (t3++ < 15000));
		t3 = 0;
		t2 = DL_TimerG_getTimerCount(TIMER_0_INST);
		
		Length_1 = t2-t1;
		if(Length_1 < 0)
		{
			Length_1 = - Length_1;
		}
		Length_1 /= 5;
		
		if(Length_1 <= 250)Length_2 = Length_1;	//ȥ���������Ӱ��
		
		return Length_2;
}

