#ifndef __KEY_FILTER_H__
#define __KEY_FILTER_H__

#include "imx6ul.h"

// 初始化按键
void keyfilter_init();
// 消抖定时器初始化
void filtertimer_init(unsigned int value);
void filtertimer_stop(void);
void filtertimer_restart(unsigned int value);
void gpio1_16_31_irqhandler(unsigned int giccIar, void *param);
void filtertimer_irqhandler(unsigned int giccIar, void *param);

#endif