#ifndef __BSP_EXIT_H__
#define __BSP_EXIT_H__
#include "imx6ul.h"

void exit_init(void); /* 中断初始化 */
void gpio1_io18_irqhandler(void); /* 中断处理函数 */

#endif // __BSP_EXIT_H__