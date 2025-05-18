#ifndef __UART_H
#define __UART_H

void Uart_init();
UART_HandleTypeDef* getUsartH();
void itoa(uint32_t Number, char* output, uint32_t Length);

#endif