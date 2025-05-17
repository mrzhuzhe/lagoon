#include <stm32f1xx_hal.h>
#include "oled.h"

void init_irq() {

    GPIO_InitTypeDef GPIO_Config = {0};

    GPIO_Config.Mode = GPIO_MODE_INPUT;
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

    GPIO_Config.Pin = GPIO_PIN_1;
    GPIO_Config.Mode = GPIO_MODE_IT_RISING | GPIO_MODE_INPUT;
    GPIO_Config.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_Config);
    
    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)1);

}

void EXTI1_IRQHandler(void) {
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)

{ 
    OLED_ShowNum(4, 4, HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1), 4);
}