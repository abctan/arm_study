#include "bsp_keyfilter.h"
#include "bsp_key.h"
#include "bsp_beep.h"
#include "bsp_int.h"
#include "bsp_gpio.h"

void keyfilter_init()
{
    key_init();
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,
                               (system_irq_handler_t)gpio1_16_31_irqhandler,
                               NULL);
    gpio_enableint(GPIO1, 18);
    filtertimer_init(66000000/100);
}

void filtertimer_init(unsigned int value)
{
    EPIT1->CR = 0;
    EPIT1->CR = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 24);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    /* 使能 EPIT1 中断并注册中断处理函数*/
    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn,
                               (system_irq_handler_t)filtertimer_irqhandler,
                               NULL);
}

void filtertimer_stop()
{
    EPIT1->CR &= ~(1<<0);
}

void filtertimer_restart(unsigned int value)
{
    EPIT1->CR &= ~(1<<0); /* 先关闭定时器 */
    EPIT1->LR = value; /* 计数值 */
    EPIT1->CR |= (1<<0); /* 打开定时器 */
}

// 按键中断函数
void gpio1_16_31_irqhandler(unsigned int giccIar, void *param)
{
    filtertimer_restart(66000000/100);
    gpio_clearintflags(GPIO1, 18);
}

// 定时器中断函数
void filtertimer_irqhandler(unsigned int giccIar, void *param)
{
    static unsigned int status = OFF;

    if (EPIT1->SR & (1<<0)) {
        filtertimer_stop();
        if(gpio_pinread(GPIO1, 18) == 0) {
            status = !status;
            beep_switch(status);
        }
    }
    EPIT1->SR |= 1<<0;
}
