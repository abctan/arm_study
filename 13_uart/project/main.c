/**************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 mian.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : I.MX6U开发板裸机实验7 按键输入实验
其他	   : 本实验主要学习如何配置I.MX6U的GPIO作为输入来使用，通过
	     开发板上的按键控制蜂鸣器的开关。
论坛 	   : www.openedv.com
在线教育	: www.yuanzige.coom
日志	   : 初版V1.0 2019/1/4 左忠凯创建
**************************************************************/
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_exit.h"
#include "bsp_int.h"
#include "bsp_epit.h"
#include "bsp_uart.h"

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	int_init(); 
	clk_init();
	clk_enable();		/* 使能所有的时钟 	     */
	led_init();			/* 初始化led 			*/
	beep_init();		/* 初始化beep	 		*/
	delay_init();
	uart_init(UART1);

	unsigned char state = OFF;
	unsigned char a=0;
	while(1)			
	{	
		puts(UART1, "请输入 1 个字符:");
		a=getc(UART1);
		putc(UART1, a);
		puts(UART1, "\r\n");

		puts(UART1, "您输入的字符为:");
		putc(UART1, a);
		puts(UART1, "\r\n\r\n");

		state = !state;
		led_switch(LED0, state);
		delayms(500);
	}

	return 0;
}
