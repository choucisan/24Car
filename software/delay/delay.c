#include "delay.h"

void delay_ms(unsigned int sx)
{
		sx=sx*32000;
		delay_cycles(sx);
}

void delay_us(unsigned int sx)
{
		sx=sx*32;
		delay_cycles(sx);
}



















