#include "bsp_uart.h"

void uart_init(UART_Type *base)
{
    uart_io_init();
    uart_disable(UART1);
    uart_softreset(UART1);

    UART1->UCR1 = 0;
    base->UCR1 &= ~(1 << 14); // 关闭自动检测波特率
    base->UCR2 |= (1 << 1) | (1 << 2) | (1 << 5) | (1 << 14);
    base->UCR3 |= 1 << 2;
    UART1->UFCR = 5<<7;
    UART1->UBIR = 71;
    UART1->UBMR = 3124;
    uart_enable(UART1); /* 使能串口 */
}

void uart_io_init()
{
	IOMUXC_SetPinMux(IOMUXC_UART1_TX_DATA_UART1_TX, 0);
    IOMUXC_SetPinMux(IOMUXC_UART1_RX_DATA_UART1_RX, 0);
	IOMUXC_SetPinConfig(IOMUXC_UART1_TX_DATA_UART1_TX, 0x10b0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_RX_DATA_UART1_RX, 0x10b0);
}

void uart_disable(UART_Type *base)
{
    base->UCR1 &= ~(1 << 0); 
}

void uart_enable(UART_Type *base)
{
    base->UCR1 |= 1 << 0;
}

void uart_softreset(UART_Type *base)
{
    base->UCR2 &= ~(1 << 0);
    while ((base->UCR2 & 0x1) == 0);
}

void putc(unsigned char c)
{
    while (((UART1->USR2 >> 3) & 0x1) == 0);
    UART1->UTXD = c & 0xFF;  // 发送数据
}

void puts(char *str)
{
    char *p = str;

    while (*p) {
        putc(*p++);
    }
}

unsigned char getc()
{
    while((UART1->USR2 & 0x1) == 0);
    return UART1->URXD;
}

int raise(int sig)
{
    return 0;
}