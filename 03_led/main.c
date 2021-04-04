#include "imx6ul.h"

// 时钟初始化
void clock_init(void)
{
    CCM->CCGR1 = 0xFFFFFFFF;
}

// LED初始化
void led_init(void)
{
    IOMUX_SW_MUX->GPIO1_IO03 = 0x5;
    IOMUX_SW_PAD->GPIO1_IO03 = 0x10B0;
    GPIO1->GDIR = 0x8;
    GPIO1->DR = 0x0;
}

// 获取led状态 0:关  1:开
volatile unsigned int get_led_status()
{
    volatile unsigned int status = (GPIO1->PSR >> 3) & 0x1;
    return status == 0 ? 1 : 0;
}

// 修改LED灯状态
void set_led_status(volatile unsigned int set_status)
{
    volatile unsigned int status;
    volatile unsigned int tmp;

    status = get_led_status();
    if (status != set_status) {
        tmp = GPIO1->GDIR & (~(0x1 << 3));
        GPIO1->DR = tmp | ((set_status & 0x1) << 3);
    }
}

// 延时函数
void delay_short(volatile unsigned int n)
{
    while(n--) {}
}
void delay(volatile unsigned int n)
{
    while(n--) {
        delay_short(0x7ff);
    }
}


int main(void)
{
    clock_init();
    led_init();

    while (1) {
        set_led_status(1);
        delay(500);
        set_led_status(0);
        delay(500);
    }

    return 0;
}
