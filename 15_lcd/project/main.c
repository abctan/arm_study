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
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"


/* 背景颜色索引 */
unsigned int backcolor[10] = {
	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

}; 
/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned char index = 0;
	unsigned char state = OFF;

	int_init(); 
	clk_init();
	clk_enable();		/* 使能所有的时钟 	     */
	led_init();			/* 初始化led 			*/
	beep_init();		/* 初始化beep	 		*/
	delay_init();
	uart_init(UART1);
	lcd_init();

	tftlcd_dev.forecolor = LCD_RED;	  
	lcd_show_string(10,10,400,32,32,(char*)"ZERO-IMX6UL ELCD TEST");  /* 显示字符串 */
	lcd_draw_rectangle(10, 52, 1014, 290);	/* 绘制矩形框  		*/
	lcd_drawline(10, 52,1014, 290);			/* 绘制线条		  	*/
	lcd_drawline(10, 290,1014, 52);			/* 绘制线条 		*/
	lcd_draw_Circle(512, 171, 119);			/* 绘制圆形 		*/

	while(1)				
	{	
		index++;
		if(index == 10)
			index = 0;
		lcd_fill(0, 300, 1023, 599, backcolor[index]);
		lcd_show_string(800,10,240,32,32,(char*)"INDEX=");  /*显示字符串				  */
		lcd_shownum(896,10, index, 2, 32); 					/* 显示数字，叠加显示	*/
		
		state = !state;
		led_switch(LED0,state);
		delayms(1000);	/* 延时一秒	*/
	}
	return 0;
}
