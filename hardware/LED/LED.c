#include "..\HARDWARE\LED\led.h"


void LED_Test(void)
{
    LEDR(1); LEDG(1); LEDB(1);
    delay_ms(200);
    LEDR(0); LEDG(0); LEDB(0);
    delay_ms(200);
}




















