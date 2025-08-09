#ifndef _UART_H_
#define _UART_H_

#include "A_include.h"


void UART_Init(void);
void UART0_Send_Bytes(uint8_t *buf, int len);
void UART0_Text(void);
//void UART1_Init(void);
void uart0_send_char(char ch);
#endif

