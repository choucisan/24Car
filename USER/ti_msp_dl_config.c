/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gMotorBackup;
DL_TimerA_backupConfig gTIMER_0Backup;
DL_TimerG_backupConfig gTIMER_0_COPYBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_Sever_init();
    SYSCFG_DL_Motor_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_TIMER_0_COPY_init();
    SYSCFG_DL_I2C_1_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_UART_1_init();
    SYSCFG_DL_ADC12_0_init();
    SYSCFG_DL_COMP_0_init();
    SYSCFG_DL_VREF_init();
    SYSCFG_DL_OPA_0_init();
    /* Ensure backup structures have no valid state */
	gMotorBackup.backupRdy 	= false;
	gTIMER_0Backup.backupRdy 	= false;
	gTIMER_0_COPYBackup.backupRdy 	= false;


}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(Motor_INST, &gMotorBackup);
	retStatus &= DL_TimerA_saveConfiguration(TIMER_0_INST, &gTIMER_0Backup);
	retStatus &= DL_TimerG_saveConfiguration(TIMER_0_COPY_INST, &gTIMER_0_COPYBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(Motor_INST, &gMotorBackup, false);
	retStatus &= DL_TimerA_restoreConfiguration(TIMER_0_INST, &gTIMER_0Backup, false);
	retStatus &= DL_TimerG_restoreConfiguration(TIMER_0_COPY_INST, &gTIMER_0_COPYBackup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerG_reset(Sever_INST);
    DL_TimerA_reset(Motor_INST);
    DL_TimerA_reset(TIMER_0_INST);
    DL_TimerG_reset(TIMER_0_COPY_INST);
    DL_I2C_reset(I2C_1_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_UART_Main_reset(UART_1_INST);
    DL_ADC12_reset(ADC12_0_INST);
    DL_COMP_reset(COMP_0_INST);
    DL_VREF_reset(VREF);
    DL_OPA_reset(OPA_0_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerG_enablePower(Sever_INST);
    DL_TimerA_enablePower(Motor_INST);
    DL_TimerA_enablePower(TIMER_0_INST);
    DL_TimerG_enablePower(TIMER_0_COPY_INST);
    DL_I2C_enablePower(I2C_1_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_UART_Main_enablePower(UART_1_INST);
    DL_ADC12_enablePower(ADC12_0_INST);
    DL_COMP_enablePower(COMP_0_INST);
    DL_VREF_enablePower(VREF);
    DL_OPA_enablePower(OPA_0_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(GPIO_Sever_C0_IOMUX,GPIO_Sever_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Sever_C0_PORT, GPIO_Sever_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_C0_IOMUX,GPIO_Motor_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_C0_PORT, GPIO_Motor_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_C1_IOMUX,GPIO_Motor_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_C1_PORT, GPIO_Motor_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_C2_IOMUX,GPIO_Motor_C2_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_C2_PORT, GPIO_Motor_C2_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_Motor_C3_IOMUX,GPIO_Motor_C3_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_Motor_C3_PORT, GPIO_Motor_C3_PIN);

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_1_IOMUX_SDA,
        GPIO_I2C_1_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_1_IOMUX_SCL,
        GPIO_I2C_1_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_1_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_1_IOMUX_SCL);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_1_IOMUX_TX, GPIO_UART_1_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_1_IOMUX_RX, GPIO_UART_1_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalOutput(LED_LEDR_IOMUX);

    DL_GPIO_initDigitalOutput(LED_LEDG_IOMUX);

    DL_GPIO_initDigitalOutput(LED_LEDB_IOMUX);

    DL_GPIO_initDigitalOutput(LED_PIN_0_IOMUX);

    DL_GPIO_initDigitalInput(KEY_KEY0_IOMUX);

    DL_GPIO_initDigitalInput(KEY_KEY1_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_SCL_IOMUX);

    DL_GPIO_initDigitalOutput(IIC_SDA_IOMUX);

    DL_GPIO_initDigitalOutput(MYSPI_MySPI_W_SCK_IOMUX);

    DL_GPIO_initDigitalOutput(MYSPI_MySPI_W_MOSI_IOMUX);

    DL_GPIO_initDigitalOutput(MYSPI_MySPI_R_MISO_IOMUX);

    DL_GPIO_initDigitalOutput(MYSPI_MySPI_W_SS_IOMUX);

    DL_GPIO_initDigitalOutput(MYSPI_OLED_RES_IOMUX);

    DL_GPIO_initDigitalOutput(MYSPI_OLED_DC_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_AIN1_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_AIN2_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_AIN3_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_AIN4_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_BIN1_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_BIN2_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_BIN3_IOMUX);

    DL_GPIO_initDigitalOutput(BT6612_BIN_4_IOMUX);

    DL_GPIO_initDigitalInput(xunji_A1_IOMUX);

    DL_GPIO_initDigitalInput(xunji_A2_IOMUX);

    DL_GPIO_initDigitalInput(xunji_A3_IOMUX);

    DL_GPIO_initDigitalInput(xunji_A4_IOMUX);

    DL_GPIO_initDigitalInput(xunji_A5_IOMUX);

    DL_GPIO_initDigitalInput(Encoder_A_IOMUX);

    DL_GPIO_initDigitalInput(Encoder_B_IOMUX);

    DL_GPIO_initDigitalInput(HC_04_ECHO_IOMUX);

    DL_GPIO_initDigitalOutput(HC_04_TRIG_IOMUX);

    DL_GPIO_clearPins(GPIOA, LED_PIN_0_PIN |
		IIC_SDA_PIN |
		MYSPI_MySPI_W_SS_PIN |
		HC_04_TRIG_PIN);
    DL_GPIO_setPins(GPIOA, BT6612_AIN1_PIN |
		BT6612_AIN2_PIN |
		BT6612_BIN1_PIN |
		BT6612_BIN2_PIN);
    DL_GPIO_enableOutput(GPIOA, LED_PIN_0_PIN |
		IIC_SDA_PIN |
		MYSPI_MySPI_W_SS_PIN |
		BT6612_AIN1_PIN |
		BT6612_AIN2_PIN |
		BT6612_BIN1_PIN |
		BT6612_BIN2_PIN |
		HC_04_TRIG_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_14_EDGE_RISE |
		DL_GPIO_PIN_13_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, Encoder_A_PIN |
		Encoder_B_PIN);
    DL_GPIO_enableInterrupt(GPIOA, Encoder_A_PIN |
		Encoder_B_PIN);
    DL_GPIO_clearPins(GPIOB, LED_LEDR_PIN |
		LED_LEDG_PIN |
		LED_LEDB_PIN |
		IIC_SCL_PIN |
		MYSPI_MySPI_W_SCK_PIN |
		MYSPI_MySPI_W_MOSI_PIN |
		MYSPI_MySPI_R_MISO_PIN |
		MYSPI_OLED_RES_PIN |
		MYSPI_OLED_DC_PIN);
    DL_GPIO_setPins(GPIOB, BT6612_AIN3_PIN |
		BT6612_AIN4_PIN |
		BT6612_BIN3_PIN |
		BT6612_BIN_4_PIN);
    DL_GPIO_enableOutput(GPIOB, LED_LEDR_PIN |
		LED_LEDG_PIN |
		LED_LEDB_PIN |
		IIC_SCL_PIN |
		MYSPI_MySPI_W_SCK_PIN |
		MYSPI_MySPI_W_MOSI_PIN |
		MYSPI_MySPI_R_MISO_PIN |
		MYSPI_OLED_RES_PIN |
		MYSPI_OLED_DC_PIN |
		BT6612_AIN3_PIN |
		BT6612_AIN4_PIN |
		BT6612_BIN3_PIN |
		BT6612_BIN_4_PIN);

}



SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);

}


/*
 * Timer clock configuration to be sourced by  / 4 (8000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   1000000 Hz = 8000000 Hz / (4 * (7 + 1))
 */
static const DL_TimerG_ClockConfig gSeverClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_4,
    .prescale = 7U
};

static const DL_TimerG_PWMConfig gSeverConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN,
    .period = 20000,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_Sever_init(void) {

    DL_TimerG_setClockConfig(
        Sever_INST, (DL_TimerG_ClockConfig *) &gSeverClockConfig);

    DL_TimerG_initPWMMode(
        Sever_INST, (DL_TimerG_PWMConfig *) &gSeverConfig);

    DL_TimerG_setCaptureCompareOutCtl(Sever_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_0_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(Sever_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
    DL_TimerG_setCaptureCompareValue(Sever_INST, 20000, DL_TIMER_CC_0_INDEX);

    DL_TimerG_enableClock(Sever_INST);


    
    DL_TimerG_setCCPDirection(Sever_INST , DL_TIMER_CC0_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 1 (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   32000000 Hz = 32000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gMotorClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gMotorConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 3200,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_Motor_init(void) {

    DL_TimerA_setClockConfig(
        Motor_INST, (DL_TimerA_ClockConfig *) &gMotorClockConfig);

    DL_TimerA_initPWMMode(
        Motor_INST, (DL_TimerA_PWMConfig *) &gMotorConfig);

    DL_TimerA_setCaptureCompareOutCtl(Motor_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_INST, 3199, DL_TIMER_CC_0_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(Motor_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_INST, 3199, DL_TIMER_CC_1_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(Motor_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_2_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_2_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_INST, 0, DL_TIMER_CC_2_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(Motor_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_3_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(Motor_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_3_INDEX);
    DL_TimerA_setCaptureCompareValue(Motor_INST, 3199, DL_TIMER_CC_3_INDEX);

    DL_TimerA_enableClock(Motor_INST);


    
    DL_TimerA_setCCPDirection(Motor_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT | DL_TIMER_CC2_OUTPUT | DL_TIMER_CC3_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   320000 Hz = 32000000 Hz / (1 * (99 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 99U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (20ms * 320000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerA_setClockConfig(TIMER_0_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerA_initTimerMode(TIMER_0_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerA_enableInterrupt(TIMER_0_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_0_INST);





}

/*
 * Timer clock configuration to be sourced by BUSCLK /  (32000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   320000 Hz = 32000000 Hz / (1 * (99 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_0_COPYClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale    = 99U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_COPY_INST_LOAD_VALUE = (100ms * 320000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_0_COPYTimerConfig = {
    .period     = TIMER_0_COPY_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC_UP,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_COPY_init(void) {

    DL_TimerG_setClockConfig(TIMER_0_COPY_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_0_COPYClockConfig);

    DL_TimerG_initTimerMode(TIMER_0_COPY_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_0_COPYTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_0_COPY_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
    DL_TimerG_enableClock(TIMER_0_COPY_INST);





}


static const DL_I2C_ClockConfig gI2C_1ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_1_init(void) {

    DL_I2C_setClockConfig(I2C_1_INST,
        (DL_I2C_ClockConfig *) &gI2C_1ClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_1_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_1_INST);

    /* Configure Controller Mode */
    DL_I2C_resetControllerTransfer(I2C_1_INST);
    /* Set frequency to 400000 Hz*/
    DL_I2C_setTimerPeriod(I2C_1_INST, 7);
    DL_I2C_setControllerTXFIFOThreshold(I2C_1_INST, DL_I2C_TX_FIFO_LEVEL_EMPTY);
    DL_I2C_setControllerRXFIFOThreshold(I2C_1_INST, DL_I2C_RX_FIFO_LEVEL_BYTES_1);
    DL_I2C_enableControllerClockStretching(I2C_1_INST);


    /* Enable module */
    DL_I2C_enableController(I2C_1_INST);


}


static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_115200_BAUD, UART_0_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_OVERRUN_ERROR |
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_UART_Main_ClockConfig gUART_1ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_1Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_1_init(void)
{
    DL_UART_Main_setClockConfig(UART_1_INST, (DL_UART_Main_ClockConfig *) &gUART_1ClockConfig);

    DL_UART_Main_init(UART_1_INST, (DL_UART_Main_Config *) &gUART_1Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9600.24
     */
    DL_UART_Main_setOversampling(UART_1_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_1_INST, UART_1_IBRD_32_MHZ_9600_BAUD, UART_1_FBRD_32_MHZ_9600_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_1_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_1_INST);
}

/* ADC12_0 Initialization */
static const DL_ADC12_ClockConfig gADC12_0ClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_ULPCLK,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_8,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC12_0_init(void)
{
    DL_ADC12_setClockConfig(ADC12_0_INST, (DL_ADC12_ClockConfig *) &gADC12_0ClockConfig);
    DL_ADC12_configConversionMem(ADC12_0_INST, ADC12_0_ADCMEM_0,
        DL_ADC12_INPUT_CHAN_2, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_DISABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_setPowerDownMode(ADC12_0_INST,DL_ADC12_POWER_DOWN_MODE_MANUAL);
    DL_ADC12_setSampleTime0(ADC12_0_INST,500);
    /* Enable ADC12 interrupt */
    DL_ADC12_clearInterruptStatus(ADC12_0_INST,(DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED));
    DL_ADC12_enableInterrupt(ADC12_0_INST,(DL_ADC12_INTERRUPT_MEM0_RESULT_LOADED));
    DL_ADC12_enableConversions(ADC12_0_INST);
}

/* COMP_0 Initialization */
static const DL_COMP_Config gCOMP_0Config = {
    .channelEnable = DL_COMP_ENABLE_CHANNEL_NONE,
    .mode          = DL_COMP_MODE_FAST,
    .negChannel    = DL_COMP_IMSEL_CHANNEL_0,
    .posChannel    = DL_COMP_IPSEL_CHANNEL_0,
    .hysteresis    = DL_COMP_HYSTERESIS_20,
    .polarity      = DL_COMP_POLARITY_NON_INV
};
static const DL_COMP_RefVoltageConfig gCOMP_0VRefConfig = {
    .mode           = DL_COMP_REF_MODE_STATIC,
    .source         = DL_COMP_REF_SOURCE_VDDA_DAC,
    .terminalSelect = DL_COMP_REF_TERMINAL_SELECT_NEG,
    .controlSelect  = DL_COMP_DAC_CONTROL_SW,
    .inputSelect    = DL_COMP_DAC_INPUT_DACCODE0
};

SYSCONFIG_WEAK void SYSCFG_DL_COMP_0_init(void)
{
    DL_COMP_init(COMP_0_INST, (DL_COMP_Config *) &gCOMP_0Config);
    DL_COMP_refVoltageInit(COMP_0_INST, (DL_COMP_RefVoltageConfig *) &gCOMP_0VRefConfig);
    DL_COMP_setDACCode0(COMP_0_INST, COMP_0_DACCODE0);

    DL_COMP_enable(COMP_0_INST);

}



static const DL_VREF_Config gVREFConfig = {
    .vrefEnable     = DL_VREF_ENABLE_ENABLE,
    .bufConfig      = DL_VREF_BUFCONFIG_OUTPUT_2_5V,
    .shModeEnable   = DL_VREF_SHMODE_DISABLE,
    .holdCycleCount = DL_VREF_HOLD_MIN,
    .shCycleCount   = DL_VREF_SH_MIN,
};

SYSCONFIG_WEAK void SYSCFG_DL_VREF_init(void) {
    DL_VREF_configReference(VREF,
        (DL_VREF_Config *) &gVREFConfig);
    delay_cycles(VREF_READY_DELAY);
}


static const DL_OPA_Config gOPA_0Config0 = {
    .pselChannel    = DL_OPA_PSEL_DAC8_OUT,
    .nselChannel    = DL_OPA_NSEL_RTOP,
    .mselChannel    = DL_OPA_MSEL_OPEN,
    .gain           = DL_OPA_GAIN_N0_P1,
    .outputPinState = DL_OPA_OUTPUT_PIN_ENABLED,
    .choppingMode   = DL_OPA_CHOPPING_MODE_DISABLE,
};

SYSCONFIG_WEAK void SYSCFG_DL_OPA_0_init(void)
{
    DL_OPA_init(OPA_0_INST, (DL_OPA_Config *) &gOPA_0Config0);
    DL_OPA_setGainBandwidth(OPA_0_INST, DL_OPA_GBW_HIGH);

    DL_OPA_enable(OPA_0_INST);
}

