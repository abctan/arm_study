#include "bsp_exit.h"
#include "bsp_gpio.h"
#include "bsp_beep.h"
#include "bsp_int.h"
#include "bsp_delay.h"

void exit_init(void)
{
    gpio_pin_config_t key_config;

    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);

    key_config.direction = kGPIO_DigitalInput;
    key_config.interruptMode = kGPIO_IntFallingEdge;
    key_config.outputLogic = 1;
    gpio_init(GPIO1, 18, &key_config);

    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);

    system_register_irqhandler(GPIO1_Combined_16_31_IRQn,
                               (system_irq_handler_t)gpio1_io18_irqhandler,
                               NULL);
    gpio_enableint(GPIO1, 18);
}

void gpio1_io18_irqhandler(void)
{
    static unsigned char state = 0;


    delayus(10);
    if(gpio_pinread(GPIO1, 18) == 0) /* 按键按下了 */
    {
        state = !state;
        beep_switch(state);
    }
    gpio_clearintflags(GPIO1, 18); /* 清除中断标志位 */
}