#include <stm32f1xx_hal.h>
#include "oled.h"

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
    
    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI1_IRQHandler(void) {
   //HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1); // Notice EXTI1-4 is ok but 5-15 cannot be trigger by IRQHandler
   // seems all gpio with GPIO_MODE_IT_RISING_FALLING can trigger exti
   HAL_GPIO_EXTI_Callback(GPIO_PIN_13);    
}

unsigned io_code = 0b11111111;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){ 
    unsigned cur_code = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) << 7;
    //unsigned cur_code = 0;
    cur_code += HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) << 6;
    cur_code += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7) << 5;
    cur_code += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) << 4;
    cur_code += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) << 3;
    cur_code += HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) << 2;
    cur_code += HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) << 1;
    cur_code += HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
    if (cur_code != io_code){
        //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)cur_code);
        io_code = cur_code;
        OLED_ShowBinNum(2, 1, io_code, 8);
    }
}