#include <stm32f1xx_hal.h>
#include "oled.h"
#include "irq.h"

int io_code = 0;
void SysTick_Handler(void)
{
    HAL_IncTick();

    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == 0){
        io_code = 1;
        //OLED_ShowNum(2, 1, io_code, 5);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)0);
    } else {
        io_code = 0;
        //OLED_ShowNum(2, 1, io_code, 5);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)1);
    }

    //HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (GPIO_PinState)1);   
    // if ((HAL_GetTick() % 5000) == 0)
    // {
    //      HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    // }

}

int main(void)
{
    HAL_Init();
    //initGPIO();
    init_irq();
    // 1kHz ticks
    HAL_SYSTICK_Config(SystemCoreClock / 1000);

    OLED_Init();
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "Fuck you!");	

    while(1) {
        // if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_SET){
        //     io_code = 1;
        //     while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_SET);
        //     //OLED_ShowNum(2, 1, io_code, 5);
        //     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
        // } else {
        //     io_code = 0;
        //     //OLED_ShowNum(2, 1, io_code, 5);
        //     HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 1);
        // }
    };

    return 0;
}
