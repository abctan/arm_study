#ifndef __UART_H__
#define __UART_H__

#include "imx6ul.h"

void uart_init(UART_Type *base);
void uart_io_init();
void uart_disable(UART_Type *base);
void uart_enable(UART_Type *base);
void uart_softreset(UART_Type *base);
void putc(UART_Type *base, unsigned char c);
void puts(UART_Type *base, char *str);
unsigned char getc(UART_Type *base);
void raise(int sig_nr);

#endif // !__UART_H__
