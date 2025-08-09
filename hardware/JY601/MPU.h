#ifndef	__MPU_H__
#define __MPU_H__

#include "A_include.h"
#include "ti_msp_dl_config.h"
// ���Կ���
/* Defines for Software_SCL: GPIOA.1 with pinCMx 2 on package pin 34 */
/* Port definition for Pin Group MPU */
#define MPU_PORT                                                         (GPIOA)

/* Defines for Software_SDA: GPIOA.0 with pinCMx 1 on package pin 33 */
#define MPU_Software_SDA_PIN                                     (DL_GPIO_PIN_0)
#define MPU_Software_SDA_IOMUX                                    (IOMUX_PINCM1)
#define MPU_Software_SCL_PIN                                     (DL_GPIO_PIN_1)
#define MPU_Software_SCL_IOMUX                                    (IOMUX_PINCM2)



#define GYRO_DEBUG	0

// ����һ���ṹ�����洢
typedef struct {
    float x;
    float y;
    float z;
} Gyro_Struct;

// ģ���ַ
#define	IIC_ADDR		0x50
// ����ǵ�ַ
#define YAW_REG_ADDR	0x3F
// �Ĵ�������
#define UN_REG			0x69
// ����Ĵ���
#define SAVE_REG		0x00
// �ǶȲο��Ĵ���
#define ANGLE_REFER_REG	0x01

//SDA����ģʽ
#define SDA_IN()   {  DL_GPIO_initDigitalInput(MPU_Software_SDA_IOMUX); }
//SDA���ģʽ
#define SDA_OUT()  {  DL_GPIO_initDigitalOutput(MPU_Software_SDA_IOMUX); \
                      DL_GPIO_enableOutput(MPU_PORT, MPU_Software_SDA_PIN); \
                   }

#define SCL(BIT)  ( BIT ? DL_GPIO_setPins(MPU_PORT,MPU_Software_SCL_PIN) : DL_GPIO_clearPins(MPU_PORT,MPU_Software_SCL_PIN) )
#define SDA(BIT)  ( BIT ? DL_GPIO_setPins(MPU_PORT,MPU_Software_SDA_PIN) : DL_GPIO_clearPins(MPU_PORT,MPU_Software_SDA_PIN) )
#define SDA_GET() ( ( DL_GPIO_readPins( MPU_PORT, MPU_Software_SDA_PIN ) & MPU_Software_SDA_PIN ) ? 1 : 0 )

void jy61pInit(void);
uint8_t readDataJy61p(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length);
uint8_t writeDataJy61p(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length);
uint8_t get_angle(void);

#endif