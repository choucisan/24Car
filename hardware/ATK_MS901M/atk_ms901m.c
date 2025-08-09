/**
 ****************************************************************************************************
 * @file        atk_ms901m.c
 * @author      ??????????(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MS901M???????????
 * @license     Copyright (c) 2020-2032, ?????????????????????
 ****************************************************************************************************
 * @attention
 *
 * ?????:??????? STM32F103??????
 * ???????:www.yuanzige.com
 * ???????:www.openedv.com
 * ??????:www.alientek.com
 * ??????:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "atk_ms901m.h"


/* ATK-MS901M UART???? */
#define ATK_MS901M_FRAME_HEAD_L             0x55
#define ATK_MS901M_FRAME_HEAD_UPLOAD_H      0x55    /* ??λ????????? */
#define ATK_MS901M_FRAME_HEAD_ACK_H         0xAF    /* ??λ????? */

/* ATK-MS901M??д?????ID */
#define ATK_MS901M_READ_REG_ID(id)         (id | 0x80)
#define ATK_MS901M_WRITE_REG_ID(id)        (id)

typedef struct
{
    uint8_t head_l;                                 /* ??λ?? */
    uint8_t head_h;                                 /* ??λ?? */
    uint8_t id;                                     /* ?ID */
    uint8_t len;                                    /* ??????? */
    uint8_t dat[ATK_MS901M_FRAME_DAT_MAX_SIZE];     /* ???? */
    uint8_t check_sum;                              /* У??? */
} atk_ms901m_frame_t;                               /* ATK-MS901M UART??????? */

typedef enum
{
    wait_for_head_l = 0x00,                         /* ?????λ?? */
    wait_for_head_h = 0x01,                         /* ?????λ?? */
    wait_for_id     = 0x02,                         /* ????ID */
    wait_for_len    = 0x04,                         /* ?????????? */
    wait_for_dat    = 0x08,                         /* ??????? */
    wait_for_sum    = 0x16,                         /* ???У??? */
} atk_ms901m_handle_state_t;                        /* ?????????????? */

/* ???????????????????? */
static const uint16_t g_atk_ms901m_gyro_fsr_table[4] = {250, 500, 1000, 2000};
static const uint8_t g_atk_ms901m_accelerometer_fsr_table[4] = {2, 4, 8, 16};

static struct
{
    uint8_t gyro;                                   /* ???????????? */
    uint8_t accelerometer;                          /* ???????????? */
} g_atk_ms901m_fsr;                                 /* ATK-MS901M?????????? */

/**
 * @brief       ???????ID???????????????
 * @param       frame  : ????????????
 *              id     : ????ID
 *              id_type: ?ID?????
 *                       ATK_MS901M_FRAME_ID_TYPE_UPLOAD: ATK-MS901M????????ID
 *                       ATK_MS901M_FRAME_ID_TYPE_ACK   : ATK-MS901M????ID
 *              timeout: ?????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK     : ??????????????
 *              ATK_MS901M_EINVAL  : ??????????????????????????
 *              ATK_MS901M_ETIMEOUT: ????????????????????????????
 */
static uint8_t atk_ms901m_get_frame_by_id(atk_ms901m_frame_t *frame, uint8_t id, uint8_t id_type, uint32_t timeout)
{
    uint8_t dat;
    atk_ms901m_handle_state_t handle_state = wait_for_head_l;
    uint8_t dat_index = 0;
    uint16_t timeout_index = 0;
    
    while (1)
    {
        if (timeout == 0)
        {
            return ATK_MS901M_ETIMEOUT;
        }
        
        if (atk_ms901m_uart_rx_fifo_read(&dat, 1) == 0)
        {
            delay_us(1);
            timeout_index++;
            if (timeout_index == 1000)
            {
                timeout_index = 0;
                timeout--;
            }
            continue;
        }
        
        switch (handle_state)
        {
            case wait_for_head_l:
            {
                if (dat == ATK_MS901M_FRAME_HEAD_L)
                {
                    frame->head_l = dat;
                    frame->check_sum = frame->head_l;
                    handle_state = wait_for_head_h;
                }
                else
                {
                    handle_state = wait_for_head_l;
                }
                break;
            }
            case wait_for_head_h:
            {
                switch (id_type)
                {
                    case ATK_MS901M_FRAME_ID_TYPE_UPLOAD:
                    {
                        if (dat == ATK_MS901M_FRAME_HEAD_UPLOAD_H)
                        {
                            frame->head_h = dat;
                            frame->check_sum += frame->head_h;
                            handle_state = wait_for_id;
                        }
                        else
                        {
                            handle_state = wait_for_head_l;
                        }
                        break;
                    }
                    case ATK_MS901M_FRAME_ID_TYPE_ACK:
                    {
                        if (dat == ATK_MS901M_FRAME_HEAD_ACK_H)
                        {
                            frame->head_h = dat;
                            frame->check_sum += frame->head_h;
                            handle_state = wait_for_id;
                        }
                        else
                        {
                            handle_state = wait_for_head_l;
                        }
                        break;
                    }
                    default:
                    {
                        return ATK_MS901M_EINVAL;
                    }
                }
                break;
            }
            case wait_for_id:
            {
                if (dat == id)
                {
                    frame->id = dat;
                    frame->check_sum += frame->id;
                    handle_state = wait_for_len;
                }
                else
                {
                    handle_state = wait_for_head_l;
                }
                break;
            }
            case wait_for_len:
            {
                if (dat > ATK_MS901M_FRAME_DAT_MAX_SIZE)
                {
                    handle_state = wait_for_head_l;
                }
                else
                {
                    frame->len = dat;
                    frame->check_sum += frame->len;
                    if (frame->len == 0)
                    {
                        handle_state = wait_for_sum;
                    }
                    else
                    {
                        handle_state = wait_for_dat;
                    }
                }
                break;
            }
            case wait_for_dat:
            {
                frame->dat[dat_index] = dat;
                frame->check_sum += frame->dat[dat_index];
                dat_index++;
                if (dat_index == frame->len)
                {
                    dat_index = 0;
                    handle_state = wait_for_sum;
                }
                break;
            }
            case wait_for_sum:
            {
                if (dat == frame->check_sum)
                {
                    return ATK_MS901M_EOK;
                }
                handle_state = wait_for_head_l;
                break;
            }
            default:
            {
                handle_state = wait_for_head_l;
                break;
            }
        }
        delay_us(1);
        timeout_index++;
        if (timeout_index == 1000)
        {
            timeout_index = 0;
            timeout--;
        }
    }
}

/**
 * @brief       ????ID???ATK-MS901M?????
 * @param       id     : ?????????????ID
 *              dat    : ???????????
 *              timeout: ?????????????????λ??????ms??
 * @retval      0: ??????
 *              ?????: ?????????????
 */
uint8_t atk_ms901m_read_reg_by_id(uint8_t id, uint8_t *dat, uint32_t timeout)
{
    uint8_t buf[7];
    uint8_t ret;
    atk_ms901m_frame_t frame = {0};
    uint8_t dat_index;
    
    buf[0] = ATK_MS901M_FRAME_HEAD_L;
    buf[1] = ATK_MS901M_FRAME_HEAD_ACK_H;
    buf[2] = ATK_MS901M_READ_REG_ID(id);
    buf[3] = 1;
    buf[4] = 0;
    buf[5] = buf[0] + buf[1] + buf[2] + buf[3] + buf[4];
    atk_ms901m_uart_send(buf, 6);
    ret = atk_ms901m_get_frame_by_id(&frame, id, ATK_MS901M_FRAME_ID_TYPE_ACK, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return 0;
    }
    
    for (dat_index=0; dat_index<frame.len; dat_index++)
    {
        dat[dat_index] = frame.dat[dat_index];
    }
    
    return frame.len;
}

/**
 * @brief       ????IDд??ATK-MS901M?????
 * @param       id : ?????????????ID
 *              len: ??д??????????1??2??
 *              dat: ??д???????
 * @retval      ATK_MS901M_EOK   : ?????д????
 *              ATK_MS901M_EINVAL: ????????len????
 */
uint8_t atk_ms901m_write_reg_by_id(uint8_t id, uint8_t len, uint8_t *dat)
{
    uint8_t buf[7];
    
    buf[0] = ATK_MS901M_FRAME_HEAD_L;
    buf[1] = ATK_MS901M_FRAME_HEAD_ACK_H;
    buf[2] = ATK_MS901M_WRITE_REG_ID(id);
    buf[3] = len;
    if (len == 1)
    {
        buf[4] = dat[0];
        buf[5] = buf[0] + buf[1] + buf[2] + buf[3] + buf[4];
        atk_ms901m_uart_send(buf, 6);
    }
    else if (len == 2)
    {
        buf[4] = dat[0];
        buf[5] = dat[1];
        buf[6] = buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5];
        atk_ms901m_uart_send(buf, 7);
    }
    else
    {
        return ATK_MS901M_EINVAL;
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ATK-MS901M?????
 * @param       buadrate: ATK-MS901M UART????????
 * @retval      ATK_MS901M_EOK  : ATK-MS901M????????
 *              ATK_MS901M_ERROR: ATK-MS901M????????
 */
uint8_t atk_ms901m_init(uint32_t baudrate)
{
    uint8_t ret;
    
    /* ATK-MS901M UART????? */
    atk_ms901m_uart_init(baudrate);  
    /* ???ATK-MS901M???????????? */
    ret = atk_ms901m_read_reg_by_id(ATK_MS901M_FRAME_ID_REG_GYROFSR, &g_atk_ms901m_fsr.gyro, 100);
    if (ret == 0)
    {
        return ATK_MS901M_ERROR;
			printf("111111111");
    }
    
    /* ???ATK-MS901M???????????? */
    ret = atk_ms901m_read_reg_by_id(ATK_MS901M_FRAME_ID_REG_ACCFSR, &g_atk_ms901m_fsr.accelerometer, 100);
    if (ret == 0)
    {
        return ATK_MS901M_ERROR;
			printf("222222");
    }
    
    return ATK_MS901M_EOK;
		printf("333333");
}

/**
 * @brief       ???ATK-MS901M?????????
 * @param       attitude_dat: ????????????
 *              timeout     : ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M???????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M????????????
 */
uint8_t atk_ms901m_get_attitude(atk_ms901m_attitude_data_t *attitude_dat, uint32_t timeout)
{
    uint8_t ret;
    atk_ms901m_frame_t frame = {0};
    
    if (attitude_dat == NULL)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_frame_by_id(&frame, ATK_MS901M_FRAME_ID_ATTITUDE, ATK_MS901M_FRAME_ID_TYPE_UPLOAD, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    attitude_dat->roll = (float)((int16_t)(frame.dat[1] << 8) | frame.dat[0]) / 32768 * 180;
    attitude_dat->pitch = (float)((int16_t)(frame.dat[3] << 8) | frame.dat[2]) / 32768 * 180;
    attitude_dat->yaw = (float)((int16_t)(frame.dat[5] << 8) | frame.dat[4]) / 32768 * 180;
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M?????????
 * @param       quaternion_dat: ????????????
 *              timeout       : ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M???????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M????????????
 */
uint8_t atk_ms901m_get_quaternion(atk_ms901m_quaternion_data_t *quaternion_dat, uint32_t timeout)
{
    uint8_t ret;
    atk_ms901m_frame_t frame = {0};
    
    if (quaternion_dat == NULL)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_frame_by_id(&frame, ATK_MS901M_FRAME_ID_QUAT, ATK_MS901M_FRAME_ID_TYPE_UPLOAD, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    quaternion_dat->q0 = (float)((int16_t)(frame.dat[1] << 8) | frame.dat[0]) / 32768;
    quaternion_dat->q1 = (float)((int16_t)(frame.dat[3] << 8) | frame.dat[2]) / 32768;
    quaternion_dat->q2 = (float)((int16_t)(frame.dat[5] << 8) | frame.dat[4]) / 32768;
    quaternion_dat->q3 = (float)((int16_t)(frame.dat[7] << 8) | frame.dat[6]) / 32768;
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M?????????????????
 * @param       gyro_dat         : ?????????????
 *              accelerometer_dat: ?????????????
 *              timeout          : ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M???????????????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M????????????????????
 */
uint8_t atk_ms901m_get_gyro_accelerometer(atk_ms901m_gyro_data_t *gyro_dat, atk_ms901m_accelerometer_data_t *accelerometer_dat, uint32_t timeout)
{
    uint8_t ret;
    atk_ms901m_frame_t frame = {0};
    
    if ((gyro_dat == NULL) && (accelerometer_dat == NULL))
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_frame_by_id(&frame, ATK_MS901M_FRAME_ID_GYRO_ACCE, ATK_MS901M_FRAME_ID_TYPE_UPLOAD, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    if (gyro_dat != NULL)
    {
        gyro_dat->raw.x = (int16_t)(frame.dat[7] << 8) | frame.dat[6];
        gyro_dat->raw.y = (int16_t)(frame.dat[9] << 8) | frame.dat[8];
        gyro_dat->raw.z = (int16_t)(frame.dat[11] << 8) | frame.dat[10];
        
        gyro_dat->x = (float)gyro_dat->raw.x / 32768 * g_atk_ms901m_gyro_fsr_table[g_atk_ms901m_fsr.gyro];
        gyro_dat->y = (float)gyro_dat->raw.y / 32768 * g_atk_ms901m_gyro_fsr_table[g_atk_ms901m_fsr.gyro];
        gyro_dat->z = (float)gyro_dat->raw.z / 32768 * g_atk_ms901m_gyro_fsr_table[g_atk_ms901m_fsr.gyro];
    }
    
    if (accelerometer_dat != NULL)
    {
        accelerometer_dat->raw.x = (int16_t)(frame.dat[1] << 8) | frame.dat[0];
        accelerometer_dat->raw.y = (int16_t)(frame.dat[3] << 8) | frame.dat[2];
        accelerometer_dat->raw.z = (int16_t)(frame.dat[5] << 8) | frame.dat[4];
        
        accelerometer_dat->x = (float)accelerometer_dat->raw.x / 32768 * g_atk_ms901m_accelerometer_fsr_table[g_atk_ms901m_fsr.accelerometer];
        accelerometer_dat->y = (float)accelerometer_dat->raw.y / 32768 * g_atk_ms901m_accelerometer_fsr_table[g_atk_ms901m_fsr.accelerometer];
        accelerometer_dat->z = (float)accelerometer_dat->raw.z / 32768 * g_atk_ms901m_accelerometer_fsr_table[g_atk_ms901m_fsr.accelerometer];
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M??????????
 * @param       magnetometer_dat: ?????????????
 *              timeout         : ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M????????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M?????????????
 */
uint8_t atk_ms901m_get_magnetometer(atk_ms901m_magnetometer_data_t *magnetometer_dat, uint32_t timeout)
{
    uint8_t ret;
    atk_ms901m_frame_t frame = {0};
    
    if (magnetometer_dat == NULL)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_frame_by_id(&frame, ATK_MS901M_FRAME_ID_MAG, ATK_MS901M_FRAME_ID_TYPE_UPLOAD, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    magnetometer_dat->x = (int16_t)(frame.dat[1] << 8) | frame.dat[0];
    magnetometer_dat->y = (int16_t)(frame.dat[3] << 8) | frame.dat[2];
    magnetometer_dat->z = (int16_t)(frame.dat[5] << 8) | frame.dat[4];
    magnetometer_dat->temperature = (float)((int16_t)(frame.dat[7] << 8) | frame.dat[6]) / 100;
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M?????????
 * @param       barometer_dat: ????????????
 *              timeout      : ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M???????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M????????????
 */
uint8_t atk_ms901m_get_barometer(atk_ms901m_barometer_data_t *barometer_dat, uint32_t timeout)
{
    uint8_t ret;
    atk_ms901m_frame_t frame = {0};
    
    if (barometer_dat == NULL)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_frame_by_id(&frame, ATK_MS901M_FRAME_ID_BARO, ATK_MS901M_FRAME_ID_TYPE_UPLOAD, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    barometer_dat->pressure = (int32_t)(frame.dat[3] << 24) | (frame.dat[2] << 16) | (frame.dat[1] << 8) | frame.dat[0];
    barometer_dat->altitude = (int32_t)(frame.dat[7] << 24) | (frame.dat[6] << 16) | (frame.dat[5] << 8) | frame.dat[4];
    barometer_dat->temperature = (float)((int16_t)(frame.dat[9] << 8) | frame.dat[8]) / 100;
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M???????
 * @param       port_dat: ??????????
 *              timeout : ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M?????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M??????????
 */
uint8_t atk_ms901m_get_port(atk_ms901m_port_data_t *port_dat, uint32_t timeout)
{
    uint8_t ret;
    atk_ms901m_frame_t frame = {0};
    
    if (port_dat == NULL)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_frame_by_id(&frame, ATK_MS901M_FRAME_ID_PORT, ATK_MS901M_FRAME_ID_TYPE_UPLOAD, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    port_dat->d0 = (uint16_t)(frame.dat[1] << 8) | frame.dat[0];
    port_dat->d1 = (uint16_t)(frame.dat[3] << 8) | frame.dat[2];
    port_dat->d2 = (uint16_t)(frame.dat[5] << 8) | frame.dat[4];
    port_dat->d3 = (uint16_t)(frame.dat[7] << 8) | frame.dat[6];
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M LED????
 * @param       state: LED????
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M LED???????
 *              ATK_MS901M_ERROR: ???ATK-MS901M LED???????
 */
uint8_t atk_ms901m_get_led_state(atk_ms901m_led_state_t *state, uint32_t timeout)
{
    uint8_t ret;
    
    ret = atk_ms901m_read_reg_by_id(ATK_MS901M_FRAME_ID_REG_LEDOFF, (uint8_t *)state, timeout);
    if (ret == 0)
    {
        return ATK_MS901M_ERROR;
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ????ATK-MS901M LED????
 * @param       state: LED????
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ????ATK-MS901M LED???????
 *              ATK_MS901M_ERROR: ????ATK-MS901M LED???????
 */
uint8_t atk_ms901m_set_led_state(atk_ms901m_led_state_t state, uint32_t timeout)
{
    uint8_t ret;
    atk_ms901m_led_state_t state_recv;
    
    ret = atk_ms901m_write_reg_by_id(ATK_MS901M_FRAME_ID_REG_LEDOFF, 1, (uint8_t *)&state);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_led_state(&state_recv, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    if (state_recv != state)
    {
        return ATK_MS901M_ERROR;
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M????????
 * @param       port   : ??????
 *              mode   : ??????
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M???????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M???????????
 */
uint8_t atk_ms901m_get_port_mode(atk_ms901m_port_t port, atk_ms901m_port_mode_t *mode, uint32_t timeout)
{
    uint8_t ret;
    uint8_t id;
    
    if (port == ATK_MS901M_PORT_D0)
    {
        id = ATK_MS901M_FRAME_ID_REG_D0MODE;
    }
    else if (port == ATK_MS901M_PORT_D1)
    {
        id = ATK_MS901M_FRAME_ID_REG_D1MODE;
    }
    else if (port == ATK_MS901M_PORT_D2)
    {
        id = ATK_MS901M_FRAME_ID_REG_D2MODE;
    }
    else if (port == ATK_MS901M_PORT_D3)
    {
        id = ATK_MS901M_FRAME_ID_REG_D3MODE;
    }
    else
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_read_reg_by_id(id, (uint8_t *)mode, timeout);
    if (ret == 0)
    {
        return ATK_MS901M_ERROR;
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ????ATK-MS901M????????
 * @param       port   : ??????
 *              mode   : ??????
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ????ATK-MS901M???????????
 *              ATK_MS901M_ERROR: ????ATK-MS901M???????????
 */
uint8_t atk_ms901m_set_port_mode(atk_ms901m_port_t port, atk_ms901m_port_mode_t mode, uint32_t timeout)
{
    uint8_t ret;
    uint8_t id;
    atk_ms901m_port_mode_t mode_recv;
    
    if (port == ATK_MS901M_PORT_D0)
    {
        if (mode == ATK_MS901M_PORT_MODE_OUTPUT_PWM)
        {
            return ATK_MS901M_ERROR;
        }
        id = ATK_MS901M_FRAME_ID_REG_D0MODE;
    }
    else if (port == ATK_MS901M_PORT_D1)
    {
        id = ATK_MS901M_FRAME_ID_REG_D1MODE;
    }
    else if (port == ATK_MS901M_PORT_D2)
    {
        if (mode == ATK_MS901M_PORT_MODE_OUTPUT_PWM)
        {
            return ATK_MS901M_ERROR;
        }
        id = ATK_MS901M_FRAME_ID_REG_D2MODE;
    }
    else if (port == ATK_MS901M_PORT_D3)
    {
        id = ATK_MS901M_FRAME_ID_REG_D3MODE;
    }
    else
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_write_reg_by_id(id, 1, (uint8_t *)&mode);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_port_mode(port, &mode_recv, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    else
    {
        if (mode_recv != mode)
        {
            return ATK_MS901M_ERROR;
        }
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M??????PWM????????
 * @param       port   : ??????
 *              pulse  : ???PWM???????????λ??????ns??
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M??????PWM??????????
 *              ATK_MS901M_ERROR: ???ATK-MS901M??????PWM???????????
 */
uint8_t atk_ms901m_get_port_pwm_pulse(atk_ms901m_port_t port, uint16_t *pulse, uint32_t timeout)
{
    uint8_t ret;
    uint8_t id;
    
    if (port == ATK_MS901M_PORT_D0)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D1)
    {
        id = ATK_MS901M_FRAME_ID_REG_D1PULSE;
    }
    else if (port == ATK_MS901M_PORT_D2)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D3)
    {
        id = ATK_MS901M_FRAME_ID_REG_D3PULSE;
    }
    else
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_read_reg_by_id(id, (uint8_t *)pulse, 100);
    if (ret == 0)
    {
        return ATK_MS901M_ERROR;
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ????ATK-MS901M??????PWM????????
 * @param       port   : ??????
 *              pulse  : ???PWM???????????λ??????ns??
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ????ATK-MS901M??????PWM??????????
 *              ATK_MS901M_ERROR: ????ATK-MS901M??????PWM???????????
 */
uint8_t atk_ms901m_set_port_pwm_pulse(atk_ms901m_port_t port, uint16_t pulse, uint32_t timeout)
{
    uint8_t ret;
    uint8_t id;
    uint16_t pulse_recv;
    
    if (port == ATK_MS901M_PORT_D0)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D1)
    {
        id = ATK_MS901M_FRAME_ID_REG_D1PULSE;
    }
    else if (port == ATK_MS901M_PORT_D2)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D3)
    {
        id = ATK_MS901M_FRAME_ID_REG_D3PULSE;
    }
    else
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_write_reg_by_id(id, 2, (uint8_t *)&pulse);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_port_pwm_pulse(port, &pulse_recv, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    if (pulse_recv != pulse)
    {
        return ATK_MS901M_ERROR;
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ???ATK-MS901M??????PWM????
 * @param       port   : ??????
 *              period : ???PWM???????λ??????ns??
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ???ATK-MS901M??????PWM??????
 *              ATK_MS901M_ERROR: ???ATK-MS901M??????PWM???????
 */
uint8_t atk_ms901m_get_port_pwm_period(atk_ms901m_port_t port, uint16_t *period, uint32_t timeout)
{
    uint8_t ret;
    uint8_t id;
    
    if (port == ATK_MS901M_PORT_D0)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D1)
    {
        id = ATK_MS901M_FRAME_ID_REG_D1PERIOD;
    }
    else if (port == ATK_MS901M_PORT_D2)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D3)
    {
        id = ATK_MS901M_FRAME_ID_REG_D3PERIOD;
    }
    else
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_read_reg_by_id(id, (uint8_t *)period, timeout);
    if (ret == 0)
    {
        return ATK_MS901M_ERROR;
    }
    
    return ATK_MS901M_EOK;
}

/**
 * @brief       ????ATK-MS901M??????PWM????
 * @param       port   : ??????
 *              period : ???PWM???????λ??????ns??
 *              timeout: ????????????????????λ??????ms??
 * @retval      ATK_MS901M_EOK  : ????ATK-MS901M??????PWM??????
 *              ATK_MS901M_ERROR: ????ATK-MS901M??????PWM???????
 */
uint8_t atk_ms901m_set_port_pwm_period(atk_ms901m_port_t port, uint16_t period, uint32_t timeout)
{
    uint8_t ret;
    uint8_t id;
    uint16_t period_recv;
    
    if (port == ATK_MS901M_PORT_D0)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D1)
    {
        id = ATK_MS901M_FRAME_ID_REG_D1PERIOD;
    }
    else if (port == ATK_MS901M_PORT_D2)
    {
        return ATK_MS901M_ERROR;
    }
    else if (port == ATK_MS901M_PORT_D3)
    {
        id = ATK_MS901M_FRAME_ID_REG_D3PERIOD;
    }
    else
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_write_reg_by_id(id, 2, (uint8_t *)&period);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    ret = atk_ms901m_get_port_pwm_period(port, &period_recv, timeout);
    if (ret != ATK_MS901M_EOK)
    {
        return ATK_MS901M_ERROR;
    }
    
    if (period_recv != period)
    {
        return ATK_MS901M_ERROR;
    }
    
    return ATK_MS901M_EOK;
}
