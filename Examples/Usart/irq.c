#include <stm32f1xx_hal.h>
#include "oled.h"
#include "uart.h"

void init_irq() {

    GPIO_InitTypeDef GPIO_Config = {0};

    GPIO_Config.Mode = GPIO_MODE_IT_RISING_FALLING | GPIO_MODE_INPUT;
    //GPIO_Config.Mode = GPIO_MODE_AF_OD;
    GPIO_Config.Pull = GPIO_PULLUP;
    //GPIO_Config.Pull = GPIO_NOPULL;
    GPIO_Config.Speed = GPIO_SPEED_FREQ_MEDIUM;

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_Config.Pin = GPIO_PIN_11 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_Config);  
    
    GPIO_Config.Pin = GPIO_PIN_7 | GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOA, &GPIO_Config);  

    GPIO_Config.Pin =  GPIO_PIN_13 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOC, &GPIO_Config);   

}