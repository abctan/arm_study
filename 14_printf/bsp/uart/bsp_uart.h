#ifndef __UART_H__
#define __UART_H__

#include "imx6ul.h"

void uart_init(UART_Type *base);
void uart_io_init();
void uart_disable(UART_Type *base);
void uart_enable(UART_Type *base);
void uart_softreset(UART_Type *base);
void putc(unsigned char c);
void puts(char *str);
unsigned char getc(void);
int raise(int sig);

#endif // !__UART_H__
