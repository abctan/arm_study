#ifndef __BSP_INT_H__
#define __BSP_INT_H__

#include "imx6ul.h"

// 中断处理函数
typedef void (*system_irq_handler_t)(unsigned int giccIar, void *param);

typedef struct _sys_irq_handle
{
    system_irq_handler_t system_irq_handler;  /* 中断函数 */
    void *user_param;                         /* 用户参数 */
} sys_irq_handle_t;

/* 函数声明 */
void int_init(void);
void system_irqtable_init(void);
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler,void *userParam);
void system_irqhandler(unsigned int giccIar);
void default_irqhandler(unsigned int giccIar, void *userParam);

#endif // !__BSP_INT_H__