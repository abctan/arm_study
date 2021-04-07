#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

// 时钟初始化
void clock_init(void)
{
    CCM->CCGR1 = 0xFFFFFFFF;
}

// LED初始化
void led_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);
    GPIO1->GDIR |= (1 << 3);
    GPIO1->DR &= ~(1 << 3);
}

// 修改LED灯状态
void set_led_status(volatile unsigned int status)
{
    volatile unsigned int tmp;
    tmp = GPIO1->DR & (~(0x1 << 3));
    GPIO1->DR = tmp | ((status & 0x1) << 3);
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
