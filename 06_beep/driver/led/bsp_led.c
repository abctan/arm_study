#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"

// LED初始化
void led_init(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03, 0x10B0);
    GPIO1->GDIR |= 0x1 << 3;
    GPIO1->DR &= ~(0x1 << 3);
}

// 修改LED灯状态
void set_led_status(volatile unsigned int status)
{
    volatile unsigned int tmp;
    tmp = GPIO1->DR & (~(0x1 << 3));
    GPIO1->DR = tmp | ((status & 0x1) << 3);
}