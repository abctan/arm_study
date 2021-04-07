#include "bsp_clk.h"
#include "bsp_time.h"
#include "bsp_led.h"


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
