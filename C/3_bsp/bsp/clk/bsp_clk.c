#include "bsp_clk.h"

/**
 * system_clk_enable() - 使能SoC上所有外设时钟
 * 
 * @param: 无
 * @return: 无
 */
void system_clk_enable(void)
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}
