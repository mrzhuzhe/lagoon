#include <stm32f1xx_hal.h>
#define LED_PORT                GPIOC 
#define LED_PIN                  
#define LED_PORT_CLK_ENABLE     __HAL_RCC_GPIOC_CLK_ENABLE

void init_irq() {

    GPIO_InitTypeDef GPIO_Config;

    GPIO_Config.Mode = GPIO_MODE_INPUT;
    GPIO_Config.Pull = GPIO_PULLUP;
    GPIO_Config.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_Config.Pin = GPIO_PIN_11;

    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_GPIO_Init(GPIOB, &GPIO_Config);  

    GPIO_Config.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_Config.Pin =  GPIO_PIN_13;
    HAL_GPIO_Init(GPIOC, &GPIO_Config); 

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)1);

}