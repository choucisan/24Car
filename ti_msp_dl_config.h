/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for Sever */
#define Sever_INST                                                         TIMG6
#define Sever_INST_IRQHandler                                   TIMG6_IRQHandler
#define Sever_INST_INT_IRQN                                     (TIMG6_INT_IRQn)
#define Sever_INST_CLK_FREQ                                              1000000
/* GPIO defines for channel 0 */
#define GPIO_Sever_C0_PORT                                                 GPIOB
#define GPIO_Sever_C0_PIN                                          DL_GPIO_PIN_6
#define GPIO_Sever_C0_IOMUX                                      (IOMUX_PINCM23)
#define GPIO_Sever_C0_IOMUX_FUNC                     IOMUX_PINCM23_PF_TIMG6_CCP0
#define GPIO_Sever_C0_IDX                                    DL_TIMER_CC_0_INDEX

/* Defines for Motor */
#define Motor_INST                                                         TIMA0
#define Motor_INST_IRQHandler                                   TIMA0_IRQHandler
#define Motor_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define Motor_INST_CLK_FREQ                                             32000000
/* GPIO defines for channel 0 */
#define GPIO_Motor_C0_PORT                                                 GPIOB
#define GPIO_Motor_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_Motor_C0_IOMUX                                      (IOMUX_PINCM25)
#define GPIO_Motor_C0_IOMUX_FUNC                     IOMUX_PINCM25_PF_TIMA0_CCP0
#define GPIO_Motor_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_Motor_C1_PORT                                                 GPIOA
#define GPIO_Motor_C1_PIN                                          DL_GPIO_PIN_9
#define GPIO_Motor_C1_IOMUX                                      (IOMUX_PINCM20)
#define GPIO_Motor_C1_IOMUX_FUNC                     IOMUX_PINCM20_PF_TIMA0_CCP1
#define GPIO_Motor_C1_IDX                                    DL_TIMER_CC_1_INDEX
/* GPIO defines for channel 2 */
#define GPIO_Motor_C2_PORT                                                 GPIOB
#define GPIO_Motor_C2_PIN                                          DL_GPIO_PIN_0
#define GPIO_Motor_C2_IOMUX                                      (IOMUX_PINCM12)
#define GPIO_Motor_C2_IOMUX_FUNC                     IOMUX_PINCM12_PF_TIMA0_CCP2
#define GPIO_Motor_C2_IDX                                    DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 3 */
#define GPIO_Motor_C3_PORT                                                 GPIOB
#define GPIO_Motor_C3_PIN                                         DL_GPIO_PIN_13
#define GPIO_Motor_C3_IOMUX                                      (IOMUX_PINCM30)
#define GPIO_Motor_C3_IOMUX_FUNC                     IOMUX_PINCM30_PF_TIMA0_CCP3
#define GPIO_Motor_C3_IDX                                    DL_TIMER_CC_3_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA1)
#define TIMER_0_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (6399U)




/* Defines for I2C_1 */
#define I2C_1_INST                                                          I2C1
#define I2C_1_INST_IRQHandler                                    I2C1_IRQHandler
#define I2C_1_INST_INT_IRQN                                        I2C1_INT_IRQn
#define I2C_1_BUS_SPEED_HZ                                                400000
#define GPIO_I2C_1_SDA_PORT                                                GPIOA
#define GPIO_I2C_1_SDA_PIN                                        DL_GPIO_PIN_16
#define GPIO_I2C_1_IOMUX_SDA                                     (IOMUX_PINCM38)
#define GPIO_I2C_1_IOMUX_SDA_FUNC                      IOMUX_PINCM38_PF_I2C1_SDA
#define GPIO_I2C_1_SCL_PORT                                                GPIOB
#define GPIO_I2C_1_SCL_PIN                                         DL_GPIO_PIN_2
#define GPIO_I2C_1_IOMUX_SCL                                     (IOMUX_PINCM15)
#define GPIO_I2C_1_IOMUX_SCL_FUNC                      IOMUX_PINCM15_PF_I2C1_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_0_FBRD_32_MHZ_115200_BAUD                                      (23)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART2
#define UART_1_INST_IRQHandler                                  UART2_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART2_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                        DL_GPIO_PIN_24
#define GPIO_UART_1_TX_PIN                                        DL_GPIO_PIN_21
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM54)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM46)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM54_PF_UART2_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM46_PF_UART2_TX
#define UART_1_BAUD_RATE                                                  (9600)
#define UART_1_IBRD_32_MHZ_9600_BAUD                                       (208)
#define UART_1_FBRD_32_MHZ_9600_BAUD                                        (21)





/* Defines for ADC12_0 */
#define ADC12_0_INST                                                        ADC0
#define ADC12_0_INST_IRQHandler                                  ADC0_IRQHandler
#define ADC12_0_INST_INT_IRQN                                    (ADC0_INT_IRQn)
#define ADC12_0_ADCMEM_0                                      DL_ADC12_MEM_IDX_0
#define ADC12_0_ADCMEM_0_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC12_0_ADCMEM_0_REF_VOLTAGE_V                                       3.3
#define GPIO_ADC12_0_C2_PORT                                               GPIOA
#define GPIO_ADC12_0_C2_PIN                                       DL_GPIO_PIN_25



/* Defines for COMP_0 */
#define COMP_0_INST                                                        COMP0
#define COMP_0_INST_INT_IRQN                                      COMP0_INT_IRQn

/* Defines for COMP_0 DACCODE0 */
#define COMP_0_DACCODE0                                                     (77)


/* GPIO configuration for COMP_0 */



/* Defines for VREF */
#define VREF_VOLTAGE_MV                                                     2500
#define GPIO_VREF_VREFPOS_PORT                                             GPIOA
#define GPIO_VREF_VREFPOS_PIN                                     DL_GPIO_PIN_23
#define GPIO_VREF_IOMUX_VREFPOS                                  (IOMUX_PINCM53)
#define GPIO_VREF_IOMUX_VREFPOS_FUNC                IOMUX_PINCM53_PF_UNCONNECTED
#define VREF_READY_DELAY                                                   (320)



/* Defines for OPA_0 */
#define OPA_0_INST                                                          OPA0
#define GPIO_OPA_0_OUT_PORT                                                GPIOA
#define GPIO_OPA_0_OUT_PIN                                        DL_GPIO_PIN_22
#define GPIO_OPA_0_IOMUX_OUT                                     (IOMUX_PINCM47)
#define GPIO_OPA_0_IOMUX_OUT_FUNC                   IOMUX_PINCM47_PF_UNCONNECTED



/* Port definition for Pin Group MPU */
#define MPU_PORT                                                         (GPIOA)

/* Defines for Software_SDA: GPIOA.0 with pinCMx 1 on package pin 33 */
#define MPU_Software_SDA_PIN                                     (DL_GPIO_PIN_0)
#define MPU_Software_SDA_IOMUX                                    (IOMUX_PINCM1)
/* Defines for LEDR: GPIOB.26 with pinCMx 57 on package pin 28 */
#define LED_LEDR_PORT                                                    (GPIOB)
#define LED_LEDR_PIN                                            (DL_GPIO_PIN_26)
#define LED_LEDR_IOMUX                                           (IOMUX_PINCM57)
/* Defines for LEDG: GPIOB.27 with pinCMx 58 on package pin 29 */
#define LED_LEDG_PORT                                                    (GPIOB)
#define LED_LEDG_PIN                                            (DL_GPIO_PIN_27)
#define LED_LEDG_IOMUX                                           (IOMUX_PINCM58)
/* Defines for LEDB: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_LEDB_PORT                                                    (GPIOB)
#define LED_LEDB_PIN                                            (DL_GPIO_PIN_22)
#define LED_LEDB_IOMUX                                           (IOMUX_PINCM50)
/* Defines for PIN_0: GPIOA.12 with pinCMx 34 on package pin 5 */
#define LED_PIN_0_PORT                                                   (GPIOA)
#define LED_PIN_0_PIN                                           (DL_GPIO_PIN_12)
#define LED_PIN_0_IOMUX                                          (IOMUX_PINCM34)
/* Defines for KEY0: GPIOA.18 with pinCMx 40 on package pin 11 */
#define KEY_KEY0_PORT                                                    (GPIOA)
#define KEY_KEY0_PIN                                            (DL_GPIO_PIN_18)
#define KEY_KEY0_IOMUX                                           (IOMUX_PINCM40)
/* Defines for KEY1: GPIOB.21 with pinCMx 49 on package pin 20 */
#define KEY_KEY1_PORT                                                    (GPIOB)
#define KEY_KEY1_PIN                                            (DL_GPIO_PIN_21)
#define KEY_KEY1_IOMUX                                           (IOMUX_PINCM49)
/* Defines for SCL: GPIOB.14 with pinCMx 31 on package pin 2 */
#define IIC_SCL_PORT                                                     (GPIOB)
#define IIC_SCL_PIN                                             (DL_GPIO_PIN_14)
#define IIC_SCL_IOMUX                                            (IOMUX_PINCM31)
/* Defines for SDA: GPIOA.30 with pinCMx 5 on package pin 37 */
#define IIC_SDA_PORT                                                     (GPIOA)
#define IIC_SDA_PIN                                             (DL_GPIO_PIN_30)
#define IIC_SDA_IOMUX                                             (IOMUX_PINCM5)
/* Defines for MySPI_W_SCK: GPIOB.16 with pinCMx 33 on package pin 4 */
#define MYSPI_MySPI_W_SCK_PORT                                           (GPIOB)
#define MYSPI_MySPI_W_SCK_PIN                                   (DL_GPIO_PIN_16)
#define MYSPI_MySPI_W_SCK_IOMUX                                  (IOMUX_PINCM33)
/* Defines for MySPI_W_MOSI: GPIOB.7 with pinCMx 24 on package pin 59 */
#define MYSPI_MySPI_W_MOSI_PORT                                          (GPIOB)
#define MYSPI_MySPI_W_MOSI_PIN                                   (DL_GPIO_PIN_7)
#define MYSPI_MySPI_W_MOSI_IOMUX                                 (IOMUX_PINCM24)
/* Defines for MySPI_R_MISO: GPIOB.15 with pinCMx 32 on package pin 3 */
#define MYSPI_MySPI_R_MISO_PORT                                          (GPIOB)
#define MYSPI_MySPI_R_MISO_PIN                                  (DL_GPIO_PIN_15)
#define MYSPI_MySPI_R_MISO_IOMUX                                 (IOMUX_PINCM32)
/* Defines for MySPI_W_SS: GPIOA.29 with pinCMx 4 on package pin 36 */
#define MYSPI_MySPI_W_SS_PORT                                            (GPIOA)
#define MYSPI_MySPI_W_SS_PIN                                    (DL_GPIO_PIN_29)
#define MYSPI_MySPI_W_SS_IOMUX                                    (IOMUX_PINCM4)
/* Defines for OLED_RES: GPIOB.17 with pinCMx 43 on package pin 14 */
#define MYSPI_OLED_RES_PORT                                              (GPIOB)
#define MYSPI_OLED_RES_PIN                                      (DL_GPIO_PIN_17)
#define MYSPI_OLED_RES_IOMUX                                     (IOMUX_PINCM43)
/* Defines for OLED_DC: GPIOB.1 with pinCMx 13 on package pin 48 */
#define MYSPI_OLED_DC_PORT                                               (GPIOB)
#define MYSPI_OLED_DC_PIN                                        (DL_GPIO_PIN_1)
#define MYSPI_OLED_DC_IOMUX                                      (IOMUX_PINCM13)
/* Defines for AIN1: GPIOA.27 with pinCMx 60 on package pin 31 */
#define BT6612_AIN1_PORT                                                 (GPIOA)
#define BT6612_AIN1_PIN                                         (DL_GPIO_PIN_27)
#define BT6612_AIN1_IOMUX                                        (IOMUX_PINCM60)
/* Defines for AIN2: GPIOA.26 with pinCMx 59 on package pin 30 */
#define BT6612_AIN2_PORT                                                 (GPIOA)
#define BT6612_AIN2_PIN                                         (DL_GPIO_PIN_26)
#define BT6612_AIN2_IOMUX                                        (IOMUX_PINCM59)
/* Defines for AIN3: GPIOB.24 with pinCMx 52 on package pin 23 */
#define BT6612_AIN3_PORT                                                 (GPIOB)
#define BT6612_AIN3_PIN                                         (DL_GPIO_PIN_24)
#define BT6612_AIN3_IOMUX                                        (IOMUX_PINCM52)
/* Defines for AIN4: GPIOB.23 with pinCMx 51 on package pin 22 */
#define BT6612_AIN4_PORT                                                 (GPIOB)
#define BT6612_AIN4_PIN                                         (DL_GPIO_PIN_23)
#define BT6612_AIN4_IOMUX                                        (IOMUX_PINCM51)
/* Defines for BIN1: GPIOA.4 with pinCMx 9 on package pin 44 */
#define BT6612_BIN1_PORT                                                 (GPIOA)
#define BT6612_BIN1_PIN                                          (DL_GPIO_PIN_4)
#define BT6612_BIN1_IOMUX                                         (IOMUX_PINCM9)
/* Defines for BIN2: GPIOA.5 with pinCMx 10 on package pin 45 */
#define BT6612_BIN2_PORT                                                 (GPIOA)
#define BT6612_BIN2_PIN                                          (DL_GPIO_PIN_5)
#define BT6612_BIN2_IOMUX                                        (IOMUX_PINCM10)
/* Defines for BIN3: GPIOB.10 with pinCMx 27 on package pin 62 */
#define BT6612_BIN3_PORT                                                 (GPIOB)
#define BT6612_BIN3_PIN                                         (DL_GPIO_PIN_10)
#define BT6612_BIN3_IOMUX                                        (IOMUX_PINCM27)
/* Defines for BIN_4: GPIOB.11 with pinCMx 28 on package pin 63 */
#define BT6612_BIN_4_PORT                                                (GPIOB)
#define BT6612_BIN_4_PIN                                        (DL_GPIO_PIN_11)
#define BT6612_BIN_4_IOMUX                                       (IOMUX_PINCM28)
/* Defines for A1: GPIOB.18 with pinCMx 44 on package pin 15 */
#define xunji_A1_PORT                                                    (GPIOB)
#define xunji_A1_PIN                                            (DL_GPIO_PIN_18)
#define xunji_A1_IOMUX                                           (IOMUX_PINCM44)
/* Defines for A2: GPIOA.3 with pinCMx 8 on package pin 43 */
#define xunji_A2_PORT                                                    (GPIOA)
#define xunji_A2_PIN                                             (DL_GPIO_PIN_3)
#define xunji_A2_IOMUX                                            (IOMUX_PINCM8)
/* Defines for A3: GPIOB.4 with pinCMx 17 on package pin 52 */
#define xunji_A3_PORT                                                    (GPIOB)
#define xunji_A3_PIN                                             (DL_GPIO_PIN_4)
#define xunji_A3_IOMUX                                           (IOMUX_PINCM17)
/* Defines for A4: GPIOB.3 with pinCMx 16 on package pin 51 */
#define xunji_A4_PORT                                                    (GPIOB)
#define xunji_A4_PIN                                             (DL_GPIO_PIN_3)
#define xunji_A4_IOMUX                                           (IOMUX_PINCM16)
/* Defines for A5: GPIOA.6 with pinCMx 11 on package pin 46 */
#define xunji_A5_PORT                                                    (GPIOA)
#define xunji_A5_PIN                                             (DL_GPIO_PIN_6)
#define xunji_A5_IOMUX                                           (IOMUX_PINCM11)
/* Port definition for Pin Group Encoder */
#define Encoder_PORT                                                     (GPIOA)

/* Defines for A: GPIOA.14 with pinCMx 36 on package pin 7 */
// pins affected by this interrupt request:["A","B","EA1","EB1"]
#define Encoder_INT_IRQN                                        (GPIOA_INT_IRQn)
#define Encoder_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define Encoder_A_IIDX                                      (DL_GPIO_IIDX_DIO14)
#define Encoder_A_PIN                                           (DL_GPIO_PIN_14)
#define Encoder_A_IOMUX                                          (IOMUX_PINCM36)
/* Defines for B: GPIOA.13 with pinCMx 35 on package pin 6 */
#define Encoder_B_IIDX                                      (DL_GPIO_IIDX_DIO13)
#define Encoder_B_PIN                                           (DL_GPIO_PIN_13)
#define Encoder_B_IOMUX                                          (IOMUX_PINCM35)
/* Defines for EA1: GPIOA.15 with pinCMx 37 on package pin 8 */
#define Encoder_EA1_IIDX                                    (DL_GPIO_IIDX_DIO15)
#define Encoder_EA1_PIN                                         (DL_GPIO_PIN_15)
#define Encoder_EA1_IOMUX                                        (IOMUX_PINCM37)
/* Defines for EB1: GPIOA.17 with pinCMx 39 on package pin 10 */
#define Encoder_EB1_IIDX                                    (DL_GPIO_IIDX_DIO17)
#define Encoder_EB1_PIN                                         (DL_GPIO_PIN_17)
#define Encoder_EB1_IOMUX                                        (IOMUX_PINCM39)
/* Port definition for Pin Group HC_SR04 */
#define HC_SR04_PORT                                                     (GPIOB)

/* Defines for ECHO: GPIOB.20 with pinCMx 48 on package pin 19 */
// pins affected by this interrupt request:["ECHO"]
#define HC_SR04_INT_IRQN                                        (GPIOB_INT_IRQn)
#define HC_SR04_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define HC_SR04_ECHO_IIDX                                   (DL_GPIO_IIDX_DIO20)
#define HC_SR04_ECHO_PIN                                        (DL_GPIO_PIN_20)
#define HC_SR04_ECHO_IOMUX                                       (IOMUX_PINCM48)
/* Defines for TRIG: GPIOB.19 with pinCMx 45 on package pin 16 */
#define HC_SR04_TRIG_PIN                                        (DL_GPIO_PIN_19)
#define HC_SR04_TRIG_IOMUX                                       (IOMUX_PINCM45)
/* Defines for Software_SCL: GPIOA.1 with pinCMx 2 on package pin 34 */
#define MPU_Software_SCL_PIN                                     (DL_GPIO_PIN_1)
#define MPU_Software_SCL_IOMUX                                    (IOMUX_PINCM2)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_Sever_init(void);
void SYSCFG_DL_Motor_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_I2C_1_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);
void SYSCFG_DL_ADC12_0_init(void);
void SYSCFG_DL_COMP_0_init(void);
void SYSCFG_DL_VREF_init(void);
void SYSCFG_DL_OPA_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
