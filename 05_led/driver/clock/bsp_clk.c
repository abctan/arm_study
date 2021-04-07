#include "bsp_clk.h"

void clock_init(void)
{
    CCM->CCGR1 = 0xFFFFFFFF;
}