#include "uart.h"
#include <stdio.h>
#include "pico/stdlib.h"

void UART_Init(void)
{
    stdio_init_all();
}

void UART_SendChar(char ch)
{
    putchar(ch);
}

void UART_SendString(const char *str)
{
    while(*str)
    {
        UART_SendChar(*(str++));
    }
}