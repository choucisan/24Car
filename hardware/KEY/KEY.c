#include "key.h"


Key_state key_s = key_release;
uint8_t Key0_Flag=0,//按键标志 随用随清
Key1_Flag=0,
Key2_Flag=0;



void KEY_Init(void)
{
    //DL_GPIO_initDigitalInput(IOMUX_PINCM49);
  DL_GPIO_initDigitalInputFeatures(IOMUX_PINCM49, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);
	DL_GPIO_initDigitalInputFeatures(IOMUX_PINCM40, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_ENABLE);
	DL_GPIO_initDigitalInputFeatures(IOMUX_PINCM52, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);
	DL_GPIO_initDigitalInputFeatures(IOMUX_PINCM51, DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);
}



uint8_t key_read(void)
{
    uint8_t key_temp = 0;

    if (DL_GPIO_readPins(GPIOA, DL_GPIO_PIN_18) == DL_GPIO_PIN_18)
    {
        key_temp |= 1; // 按键1按下
    }
    if (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_21) == DL_GPIO_PIN_21)
    {
        key_temp |= 2; // 按键2按下
    }
    return key_temp;
}

uint8_t key_value = 0; // 按键值
uint8_t key_old = 0; // 上一次按键值


void key_scan(void)
{
    key_value = key_read(); // 读取当前按键值

    // 检测按键按下
    if ((key_value & 1) && !(key_old & 1)) // 按键1按下
    {
        mode_flag++;
        mode_flag %= 7;
    }
    if ((key_value & 2) && !(key_old & 2)) // 按键2按下
    {
        enter_flag = mode_flag;	
			Last_YAW_out = YAW_out;
    }

    // 更新按键状态
    key_old = key_value;
}








