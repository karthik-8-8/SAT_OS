#ifndef UART_H
#define UART_H

#include "sat_os.h"

void UART_Init(void);

void UART_SendChar(char ch);

void UART_SendString(const char *str);


#endif