#ifndef __BSP_LED_H__
#define __BSP_LED_H__

// LED初始化
void led_init(void);
// 获取led状态 0:关  1:开
volatile unsigned int get_led_status();
// 修改LED灯状态
void set_led_status(volatile unsigned int set_status);

#endif // !__BSP_LED_H__