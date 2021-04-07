#include "bsp_clk.h"
#include "bsp_time.h"
#include "bsp_led.h"
#include "bsp_beep.h"


int main(void)
{
    clock_init();
    led_init();
    beep_init();

    while (1) {
        set_led_status(1);
        beep_set_status(TRUE);
        delay(500);
        set_led_status(0);
        beep_set_status(FALSE);
        delay(500);
    }

    return 0;
}
