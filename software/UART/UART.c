#include "uart.h"


#if 1

#if (__ARMCC_VERSION >= 6010050)            /* ʹ��AC6������ʱ */
__asm(".global __use_no_semihosting\n\t");  /* ������ʹ�ð�����ģʽ */
__asm(".global __ARM_use_no_argv \n\t");    /* AC6����Ҫ����main����Ϊ�޲�����ʽ�����򲿷����̿��ܳ��ְ�����ģʽ */

#else

#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;

};

#endif

/* ��ʹ�ð�����ģʽ��������Ҫ�ض���_ttywrch\_sys_exit\_sys_command_string����,��ͬʱ����AC6��AC5ģʽ */
int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

/* ����_sys_exit()�Ա���ʹ�ð�����ģʽ */
void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}


/* FILE �� stdio.h���涨��. */
FILE __stdout;

/* MDK����Ҫ�ض���fputc����, printf�������ջ�ͨ������fputc����ַ��������� */
int fputc(int ch, FILE *f)
{

    DL_UART_Main_transmitDataBlocking(UART_0_INST, (uint8_t)ch);
    return ch;
}
#endif
void UART0_Text(void)
{
    uint8_t send_test[13]={"hello world!\n"};
//    uint8_t *p={"hello world!\n"};
    UART0_Send_Bytes(send_test,sizeof(send_test));
//    UART0_Send_Bytes(p,sizeof(p));
}


void UART0_Send_Bytes(uint8_t *buf, int len)
{
  while(len--)
  {
    DL_UART_Main_transmitDataBlocking(UART_0_INST, *buf);
    buf++;
  }
}

void uart0_send_char(char ch)
{
    //������3æ��ʱ��ȴ�����æ��ʱ���ٷ��ʹ��������ַ�
    while( DL_UART_isBusy(UART_0_INST) == true );
    DL_UART_Main_transmitData(UART_0_INST, ch);
}
void UART_Init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);//���жϹ���
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);//ʹ�ܴ����ж�
}




