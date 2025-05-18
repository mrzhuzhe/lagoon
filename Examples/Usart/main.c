#include <stm32f1xx_hal.h>
#include "oled.h"
#include "irq.h"
#include "uart.h"

int main(void)
{
    HAL_Init();
    // 1kHz ticks
    HAL_SYSTICK_Config(SystemCoreClock / 1000);
    
    OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "Fuck you!");
    OLED_ShowBinNum(2, 1, 0b11111111, 8);

    init_irq();
    Uart_init();

    while(1);

    return 0;
}
