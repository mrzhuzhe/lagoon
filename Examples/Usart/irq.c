#include <stm32f1xx_hal.h>
#include "oled.h"
#include "uart.h"

uint32_t u_pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

void itoa(uint32_t Number, char* output, uint32_t Length){
	for (uint8_t i = 0; i < Length; i++)							
	{
		output[i] = Number / u_pow(2, Length - i - 1) % 2 + '0';
	}
}

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

    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    // Error EXTI9_5_IRQn will crash
    // HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void EXTI1_IRQHandler(void) {
   //HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1); // Notice EXTI1-4 is ok but 5-15 cannot be trigger by IRQHandler
   // seems all gpio with GPIO_MODE_IT_RISING_FALLING can trigger exti
   HAL_GPIO_EXTI_Callback(GPIO_PIN_13);    
}

void EXTI3_IRQHandler(void) {
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void EXT9_5_IRQHandler(void) {
   //HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5 | GPIO_PIN_7);
   // Error this dont work
   HAL_GPIO_EXTI_Callback(GPIO_PIN_13); 
}

void EXTI15_10_IRQHandler(void) {
   HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_15);
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
        uint8_t Test[10] = "12345678\n";
        itoa(io_code, Test, 8);
        HAL_USART_Transmit(getUsartH(), (uint8_t*)Test, sizeof(Test), 10);
    }
    
}