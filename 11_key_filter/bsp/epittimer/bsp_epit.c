#include "bsp_epit.h"
#include "bsp_int.h"
#include "bsp_led.h"

void epit_init(unsigned int frac, unsigned int value)
{
    if (frac > 4096) {
        frac = 4096;
    }
    
    EPIT1->CR = 0;
    EPIT1->CR = (1 << 1) | (1 << 2) | (1 << 3) | (frac << 4) | (1 << 24);
    EPIT1->LR = value;
    EPIT1->CMPR = 0;

    GIC_EnableIRQ(EPIT1_IRQn);

    system_register_irqhandler(EPIT1_IRQn, (system_irq_handler_t)epit1_irqhandler, NULL);
    EPIT1->CR |= 1 << 0; 
}

void epit1_irqhandler(unsigned int giccIar, void *param)
{
    static unsigned int status = 0;

    if (EPIT1->SR & 0x1) {
        status = !status;
        led_switch(LED0, status); /* 定时器周期到，反转 LED */
    }

    EPIT1->SR |= 1 << 0;
}