#include <stm32f1xx_hal.h>
#include "oled.h"
#include "irq.h"
#include "uart.h"
#include <string.h>

uint8_t Test[10] = "11111111\n";
unsigned io_code = 0b11111111;
void SysTick_Handler(void)
{
    HAL_IncTick();
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
        itoa(io_code, Test, 8);
        while(HAL_UART_Transmit(getUsartH(), (uint8_t*)Test, sizeof(Test), 10));
    }    
}

int main(void)
{
    HAL_Init();
    init_irq();
    Uart_init();

    // 1kHz ticks
    HAL_SYSTICK_Config(SystemCoreClock / 1000);
    
    OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "Fuck you!");
    OLED_ShowBinNum(2, 1, 0b11111111, 8);
    OLED_ShowString(3, 1, "R: ");  
    while(1);

    return 0;
}
