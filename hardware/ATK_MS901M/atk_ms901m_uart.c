/**
 ****************************************************************************************************
 * @file        atk_ms901m_uart.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MS901Mģ��UART�ӿ���������
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "atk_ms901m_uart.h"
#include "..\software\uart\uart.h"

static DL_UART_Main_Config g_uart_handle;            /* ATK-MS901M UART */
static struct
{
    uint8_t buf[ATK_MS901M_UART_RX_FIFO_BUF_SIZE];  /* ���� */
    uint16_t size;                                  /* �����С */
    uint16_t reader;                                /* ��ָ�� */
    uint16_t writer;                                /* дָ�� */
} g_uart_rx_fifo;                                   /* UART����FIFO */

/**
 * @brief       ATK-MS901M UART����FIFOд������
 * @param       dat: ��д������
 *              len: ��д�����ݵĳ���
 * @retval      0: ����ִ�гɹ�
 *              1: FIFOʣ��ռ䲻��
 */
uint8_t atk_ms901m_uart_rx_fifo_write(uint8_t *dat, uint16_t len)
{
    uint16_t i;
    

    for (i=0; i<len; i++)
    {
        g_uart_rx_fifo.buf[g_uart_rx_fifo.writer] = dat[i];
        g_uart_rx_fifo.writer = (g_uart_rx_fifo.writer + 1) % g_uart_rx_fifo.size;
    }
    
    return 0;
}

/**
 * @brief       ATK-MS901M UART����FIFO��ȡ����
 * @param       dat: ��ȡ���ݴ��λ��
 *              len: ����ȡ���ݵĳ���
 * @retval      0: FIFO��������
 *              ����ֵ: ʵ�ʶ�ȡ�����ݳ���
 */
uint16_t atk_ms901m_uart_rx_fifo_read(uint8_t *dat, uint16_t len)
{
    uint16_t fifo_usage;
    uint16_t i;
    
    /* ��ȡFIFO��ʹ�ô�С */
    if (g_uart_rx_fifo.writer >= g_uart_rx_fifo.reader)
    {
        fifo_usage = g_uart_rx_fifo.writer - g_uart_rx_fifo.reader;
    }
    else
    {
        fifo_usage = g_uart_rx_fifo.size - g_uart_rx_fifo.reader + g_uart_rx_fifo.writer;
    }
    
    /* FIFO���������� */
    if (len > fifo_usage)
    {
        len = fifo_usage;
    }
    

    for (i=0; i<len; i++)
    {
        dat[i] = g_uart_rx_fifo.buf[g_uart_rx_fifo.reader];
        g_uart_rx_fifo.reader = (g_uart_rx_fifo.reader + 1) % g_uart_rx_fifo.size;
    }
    
    return len;
}

/**
 * @brief       ATK-MS901M UART����FIFO���
 * @param       ��
 * @retval      ��
 */
void atk_ms901m_rx_fifo_flush(void)
{
    g_uart_rx_fifo.writer = g_uart_rx_fifo.reader;
}

/**
 * @brief       ATK-MS901M UART��������
 * @param       dat: �����͵�����
 *              len: ���������ݵĳ���
 * @retval      ��
 */
void atk_ms901m_uart_send(char *dat, uint8_t len)
{
    //HAL_UART_Transmit(&g_uart_handle, dat, len, HAL_MAX_DELAY);
	      //��ǰ�ַ�����ַ���ڽ�β ���� �ַ����׵�ַ��Ϊ��
    while(*dat!=0&&dat!=0)
    {
        //�����ַ����׵�ַ�е��ַ��������ڷ������֮���׵�ַ����
        uart0_send_char(*dat++);
    }
}

/**
 * @brief       ATK-MS901M UART��ʼ��
 * @param       baudrate: UARTͨѶ������
 * @retval      ��
 */
void atk_ms901m_uart_init(uint32_t baudrate)
{                                                                   
    g_uart_rx_fifo.size = ATK_MS901M_UART_RX_FIFO_BUF_SIZE;         /* UART����FIFO�����С */
    g_uart_rx_fifo.reader = 0;                                      /* UART����FIFO��ָ�� */
    g_uart_rx_fifo.writer = 0;                                      /* UART����FIFOдָ�� */
}

/**
 * @brief       ATK-MS901M UART�жϻص�����
 * @param       ��
 * @retval      ��
 */
void UART_0_INST_IRQHandler(void)
{
    uint8_t tmp;
	switch( DL_UART_getPendingInterrupt(UART_0_INST) )
	{
		case DL_UART_IIDX_OVERRUN_ERROR:
			DL_UART_getRawInterruptStatus(UART_0_INST,DL_UART_IIDX_OVERRUN_ERROR);
		  DL_UART_Main_receiveData(UART_0_INST);
			break;
		case DL_UART_IIDX_RX://����ǽ����ж�			
			// ���շ��͹��������ݱ���
			tmp = DL_UART_Main_receiveData(UART_0_INST);
      atk_ms901m_uart_rx_fifo_write(&tmp, 1);
			break;	
		default://�����Ĵ����ж�
			break;
	}
	DL_UART_clearInterruptStatus(UART_0_INST,DL_UART_IIDX_OVERRUN_ERROR);
	
}
