#include <stm32f1xx_hal.h>
#include "oled.h"
#include "irq.h"

GPIO_PinState io_code = 1;
void SysTick_Handler(void)
{
    HAL_IncTick();
    GPIO_PinState cur_code = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
    if (cur_code != io_code){
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)cur_code);
        io_code = cur_code;
        OLED_ShowBinNum(2, 1, io_code, 8);
    }
}

int main(void)
{
    HAL_Init();
    init_irq();
    // 1kHz ticks
    HAL_SYSTICK_Config(SystemCoreClock / 1000);

    OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "Fuck you!");
    OLED_ShowBinNum(2, 1, io_code, 8);
    while(1);

    return 0;
}
