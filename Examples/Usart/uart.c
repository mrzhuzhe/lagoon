#include <stm32f1xx_hal.h>
#include "oled.h"

USART_HandleTypeDef UsartHandle;

void Uart_init(){

	
    GPIO_InitTypeDef  GPIO_InitStruct;
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE(); 
    
    // stty -F /dev/ttyUSB0 115200 cs8 -cstopb -parenb -echo -icanon -onlcr
    GPIO_InitStruct.Pin       = GPIO_PIN_9;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
    // HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    // HAL_NVIC_EnableIRQ(USART1_IRQn);

	UsartHandle.Instance        = USART1;

    UsartHandle.Init.BaudRate   = 115200;
    UsartHandle.Init.WordLength = USART_WORDLENGTH_8B;
    UsartHandle.Init.StopBits   = USART_STOPBITS_1;
    UsartHandle.Init.Parity     = USART_PARITY_NONE;
    //UsartHandle.Init.HwFlowCtl  = USART_HWCONTROL_NONE;
    UsartHandle.Init.Mode       = USART_MODE_TX_RX;
    HAL_USART_Init(&UsartHandle);

    uint8_t Test[] = "Hello World !!!\r\n"; 
    HAL_USART_Transmit(&UsartHandle, Test, sizeof(Test), 10);

}

// void HAL_USART_RxCpltCallback(USART_HandleTypeDef *husart) {
//    OLED_ShowBinNum(2, 1, 123, 8); 
// }