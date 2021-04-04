#include "main.h"

// 时钟初始化
void clock_init(void)
{
    CCM_CCGR0 = 0xFFFFFFFF;
    CCM_CCGR1 = 0xFFFFFFFF;
    CCM_CCGR2 = 0xFFFFFFFF;
    CCM_CCGR3 = 0xFFFFFFFF;
    CCM_CCGR4 = 0xFFFFFFFF;
    CCM_CCGR5 = 0xFFFFFFFF;
    CCM_CCGR6 = 0xFFFFFFFF;
}

// LED初始化
void led_init(void)
{
    IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03 = 0x5;
    IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03 = 0x10B0;
    GPIO1_GDIR = 0x8;
    GPIO1_DR = 0x0;
}

// 获取led状态 0:关  1:开
volatile unsigned int get_led_status()
{
    volatile unsigned int status = (GPIO1_PSR >> 3) & 0x1;
    return status == 0 ? 1 : 0;
}

// 修改LED灯状态
void set_led_status(volatile unsigned int set_status)
{
    //volatile unsigned int status;
    volatile unsigned int tmp;

    //status = get_led_status();
    //if (status != set_status) {
        tmp = GPIO1_DR & (~(0x1 << 3));
        GPIO1_DR = tmp | ((set_status & 0x1) << 3);
    //}
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
        // GPIO1_DR &= ~(1<<3);
        delay(500);
        // GPIO1_DR |= (1<<3);
        set_led_status(0);
        delay(500);
    }

    return 0;
}
