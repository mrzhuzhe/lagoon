#include <stm32f1xx_hal.h>
#include "oled.h"

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

UART_HandleTypeDef UartHandle;

char ReceiveText[10] = "Init txt\n";

void Uart_init(){

	
    GPIO_InitTypeDef  GPIO_InitStruct;
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
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
        
	UartHandle.Instance        = USART1;
    UartHandle.Init.BaudRate   = 38400;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;
    HAL_UART_Init(&UartHandle);

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    
    // Interrupt callback regist only can be call once 
    HAL_UART_Receive_IT(&UartHandle, ReceiveText, sizeof(ReceiveText));
}

UART_HandleTypeDef* getUsartH(){
    return &UartHandle;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_UART_Transmit(&UartHandle, ReceiveText, sizeof(ReceiveText), 10);
    // Interrupt callback regist only can be call once , so regist a new one for next interrupt 
    HAL_UART_Receive_IT(&UartHandle, ReceiveText, sizeof(ReceiveText));
    
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart){
    char Text[10] = {0};
    itoa((unsigned)huart->ErrorCode, Text, 10);
    HAL_UART_Transmit(&UartHandle, Text, sizeof(Text), 10);
}

void USART1_IRQHandler(void) {   
   HAL_UART_IRQHandler(&UartHandle);
}


