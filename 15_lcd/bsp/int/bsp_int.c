#include "bsp_int.h"

static unsigned int irqNesting;
static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS];

void int_init(void)
{
    GIC_Init();
    system_irqtable_init();
    __set_VBAR((uint32_t)0x87800000);
}


void system_irqtable_init(void)
{
    unsigned int i;
    irqNesting = 0;

    for (i = 0; i < NUMBER_OF_INT_VECTORS; i++) {
        system_register_irqhandler((IRQn_Type)i, default_irqhandler, NULL);
    }
}


void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *userParam)
{
    irqTable[irq].system_irq_handler = handler;
    irqTable[irq].user_param = userParam;
}

// 进入irq模式后调用的函数
void system_irqhandler(unsigned int giccIar)
{
    uint32_t intNum = giccIar & 0x3FFUL;

    if ((intNum == 1020) || (intNum >= NUMBER_OF_INT_VECTORS)) {
        return;
    }

    irqNesting++; /* 中断嵌套计数器加一 */
    // 根据中断id调用对应的中断函数
    irqTable[intNum].system_irq_handler(intNum, irqTable[intNum].user_param);
    irqNesting--; /* 中断嵌套计数器减一 */
}

// 默认中断函数
void default_irqhandler(unsigned int giccIar, void *userParam)
{
    
}