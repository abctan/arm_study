#include "bsp_gpio.h"
/***************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 bsp_gpio.h
作者	   : 左忠凯
版本	   : V1.0
描述	   : GPIO操作文件。
其他	   : 无
论坛 	   : www.openedv.com
日志	   : 初版V1.0 2019/1/4 左忠凯创建
***************************************************************/

/*
 * @description		: GPIO初始化。
 * @param - base	: 要初始化的GPIO组。
 * @param - pin		: 要初始化GPIO在组内的编号。
 * @param - config	: GPIO配置结构体。
 * @return 			: 无
 */
void gpio_init(GPIO_Type *base, int pin, gpio_pin_config_t *config)
{
	if(config->direction == kGPIO_DigitalInput) /* 输入 */
	{
		base->GDIR &= ~( 1 << pin);
	}
	else										/* 输出 */
	{
		base->GDIR |= 1 << pin;
		gpio_pinwrite(base,pin, config->outputLogic);/* 设置默认输出电平 */
	}

	gpio_intconfig(base, pin, config->interruptMode);
}

 /*
  * @description	 : 读取指定GPIO的电平值 。
  * @param - base	 : 要读取的GPIO组。
  * @param - pin	 : 要读取的GPIO脚号。
  * @return 		 : 无
  */
 int gpio_pinread(GPIO_Type *base, int pin)
 {
	 return (((base->DR) >> pin) & 0x1);
 }

 /*
  * @description	 : 指定GPIO输出高或者低电平 。
  * @param - base	 : 要输出的的GPIO组。
  * @param - pin	 : 要输出的GPIO脚号。
  * @param - value	 : 要输出的电平，1 输出高电平， 0 输出低低电平
  * @return 		 : 无
  */
void gpio_pinwrite(GPIO_Type *base, int pin, int value)
{
	 if (value == 0U)
	 {
		 base->DR &= ~(1U << pin); /* 输出低电平 */
	 }
	 else
	 {
		 base->DR |= (1U << pin); /* 输出高电平 */
	 }
}

void gpio_intconfig(GPIO_Type* base, unsigned int pin, gpio_interrupt_mode_t pinInterruptMode)
{
	volatile uint32_t *icr = NULL;

	base->EDGE_SEL &= ~(0x1 << pin);
	if (pin < 16) {
		icr = &(base->ICR1);
	} else {
		icr = &(base->ICR2);
		pin -= 16;
	}

	switch (pinInterruptMode) {
		case kGPIO_IntLowLevel:
			*icr &= ~(0x3 << (pin * 2));
			break;
		case kGPIO_IntHighLevel:
			*icr = (*icr & ~(0x3 << (pin * 2))) | (0x1 << (pin * 2));
			break;
		case kGPIO_IntRisingEdge:
			*icr = (*icr & (~(0x3 << (2 * pin)))) | (0x2 << (2 * pin));
			break;
		case kGPIO_IntFallingEdge:
			*icr |= (0x3 << (2 * pin));
			break;
		case kGPIO_IntRisingOrFallingEdge:
			base->EDGE_SEL |= (0x1 << pin);
			break;
		default:
			break;
	}
}

void gpio_enableint(GPIO_Type* base, unsigned int pin)
{
	base->IMR |= (0x1 << pin);
}

void gpio_disableint(GPIO_Type* base, unsigned int pin)
{
	base->IMR &= ~(0x1 << pin);
}

void gpio_clearintflags(GPIO_Type* base, unsigned int pin)
{
	base->ISR |= (0x1 << pin);
}



