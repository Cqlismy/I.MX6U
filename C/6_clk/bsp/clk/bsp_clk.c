#include "bsp_clk.h"

/**
 * clk_enable() - 使能SoC上所有外设时钟 
 */
void clk_enable(void)
{
    CCM->CCGR0 = 0xffffffff;
    CCM->CCGR1 = 0xffffffff;
    CCM->CCGR2 = 0xffffffff;
    CCM->CCGR3 = 0xffffffff;
    CCM->CCGR4 = 0xffffffff;
    CCM->CCGR5 = 0xffffffff;
    CCM->CCGR6 = 0xffffffff;
}

/**
 * imx6ul_clk_init() - 初始化系统时钟为528MHz
 * 并设置PLL2、PLL3的各个PFD时钟 
 */
void imx6ul_clk_init(void)
{
    unsigned int reg = 0;

    /* 1、设置ARM内核时钟为528MHz
     * 1.1、先判断当前使用哪个时钟源启动，正常情况下由
     * pll1_sw_clk驱动，该pll1_sw_clk有两个来源，分别为
     * pll1_main_clk和teq_clk，当ARM内核需要配置528MHz，
     * 需选择pll1_main_clk为pll1时钟源，在修改pll1_main_clk
     * 时钟之前需要将pll1_sw_clk从pll1_main_clk切换到
     * step_clk，修改完成后，将pll1_sw_clk切换回pll1_main_clk，
     * 其中step_clk等于24MHz。
     */
}