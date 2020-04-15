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
    if((((CCM->CCSR) >> 2) & 0x1) == 0) { /*判断是否pll1_main_clk */
        CCM->CCSR &= ~(1 << 8); /* 设置step_clk时钟源24MHz OSC */
        CCM->CCSR |= (1 << 2); /* 设置pll1_sw_clk时钟源step_clk */
    }

    /*
     * 1.2、设置pll1_main_clk为1056MHz，528MHz*2=1056MHz
     * pll1_sw_clk到ARM内核将被2分频。
     * 配置CCM_ANLOG->PLL_ARM寄存器
     * bit[13]: 1 使能时钟输出
     * bit[6:0]: 88 Fout = Fin * div_select / 2
     * 要设置1056MHz的话，div_select = 88。
     */
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 < 0) & 0x7F);
    CCM->CCSR &= ~(1 << 2); /* 将pll_sw_clk时钟切换回pll1_main_clk */
    CCM->CACRR &= ~(0x7 << 0);
    CCM->CACRR |= 1; /* ARM内核时钟为pll1_sw_clk/2=1056MHz/2=528MHz */

    /* 2、设置PLL2(System PLL)的各个PFD */

    /* 3、设置PLL3(USB1 PLL)的各个PFD */

    /* 4、设置AHB时钟，最小为6MHz，最大为132MHz */

    /* 5、设置IPG_CLK_ROOT时钟，最小为3MHz，最大为66MHz */

    /* 6、设置PERCLK_CLK_ROOT时钟 */
}