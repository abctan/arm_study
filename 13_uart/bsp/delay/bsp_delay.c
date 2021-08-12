/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_delay.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : 延时文件。
其他	   : 无
论坛 	   : www.openedv.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
***************************************************************/
#include "imx6ul.h"

void delay_init(void)
{
	GPT1->CR = 0;
	GPT1->CR = 1 << 15;
	while((GPT1->CR >> 15) & 0x1);
	GPT1->CR = (1<<6);
	GPT1->PR = 65;
	GPT1->OCR[0] = 0XFFFFFFFF;
	GPT1->CR |= 1<<0;
}

void delayus(unsigned int usdelay)
{
	unsigned long oldcnt, newcnt;
	unsigned long tcntvalue = 0; /* 走过的总时间 */

	oldcnt = GPT1->CNT;

	while (1) {
		newcnt = GPT1->CNT;
		if (newcnt != oldcnt) {
			if (newcnt > oldcnt) {
				tcntvalue += newcnt - oldcnt;
			} else {
				tcntvalue += 0xFFFFFFFF - oldcnt + newcnt;
			}

			if (tcntvalue >= usdelay) {
				break;
			}
		}
	}
}

void delayms(unsigned int msdelay)
{
	int i = 0;
	for(i = 0; i < msdelay; i++) {
		delayus(1000);
	}
}

