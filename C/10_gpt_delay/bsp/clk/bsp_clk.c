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

/**
 * imx6ul_clk_init() - 初始化系统时钟为528MHz
 * 并设置PLL2、PLL3的各个PFD时钟
 * 
 * @param: 无
 * @return: 无 
 */
void imx6ul_clk_init(void)
{
    unsigned int reg = 0;

    /**
     * 1、设置ARM内核时钟为528MHz
     * 1.1、先判断当前使用哪个时钟源启动，正常情况下由
     * pll1_sw_clk驱动，该pll1_sw_clk有两个来源，分别为
     * pll1_main_clk和teq_clk，当ARM内核需要配置528MHz，
     * 需选择pll1_main_clk为pll1时钟源，在修改pll1_main_clk
     * 时钟之前需要将pll1_sw_clk从pll1_main_clk切换到
     * step_clk，修改完成后，将pll1_sw_clk切换回pll1_main_clk，
     * 其中step_clk等于24MHz。
     */
    if((((CCM->CCSR) >> 2) & 0x1) == 0) { /*判断是否pll1_main_clk */
        CCM->CCSR &= ~(1 << 8);           /* 设置step_clk时钟源24MHz OSC */
        CCM->CCSR |= (1 << 2);            /* 设置pll1_sw_clk时钟源step_clk */
    }

    /**
     * 1.2、设置pll1_main_clk为1056MHz，528MHz*2 = 1056MHz
     * pll1_sw_clk到ARM内核将被2分频。
     * 配置CCM_ANLOG->PLL_ARM寄存器
     * bit[13]: 1 使能时钟输出
     * bit[6:0]: 88 Fout = Fin * div_select / 2
     * 要设置1056MHz的话，div_select = 88。
     */
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 < 0) & 0x7f);
    CCM->CCSR &= ~(1 << 2);         /* 将pll_sw_clk时钟切换回pll1_main_clk */
    CCM->CACRR &= ~(0x7 << 0);
    CCM->CACRR |= 1;                /* ARM内核时钟为pll1_sw_clk/2=1056MHz/2 = 528MHz */

    /* 2、设置PLL2(System PLL)的各个PFD */
    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3f3f3f3f);       /* 将原来的配置清空 */
    reg |= 32 << 24;            /* PLL2_PFD3 = 528MHz * 18/32 = 297MHz */
    reg |= 24 << 16;            /* PLL2_PFD2 = 528MHz * 18/24 = 396MHz */
    reg |= 16 << 8;             /* PLL2_PFD1 = 528MHz * 18/16 = 594MHz */
    reg |= 27 << 0;             /* PLL2_PFD0 = 528MHz * 18/27 = 352MHz */
    CCM_ANALOG->PFD_528 = reg;  /* 设置PLL2_PFD0~3相关的时钟 */

    /* 3、设置PLL3(USB1 PLL)的各个PFD */
    reg = 0;                    /* 先清0 */
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0x3f3f3f3f);
    reg |= 19 << 24;            /* PLL3_PFD3 = 480MHz * 18/19 = 454.74MHz */
    reg |= 17 << 16;            /* PLL3_PFD2 = 480MHz * 18/17 = 508.24MHz */
    reg |= 16 << 8;             /* PLL3_PFD1 = 480MHz * 18/16 = 540MHz */
    reg |= 12 << 0;             /* PLL3_PFD0 = 480MHz * 18/12 = 720MHz */
    CCM_ANALOG->PFD_480 = reg;  /* 设置PLL3_PFD0~3相关的时钟 */

    /* 4、设置AHB时钟，最小为6MHz，最大为132MHz */
    CCM->CBCMR &= ~(3 << 18);       /* 将寄存器原来的配置清除 */
    CCM->CBCMR |= (1 << 18);        /* pre_periph_clk = PLL2_PFD2 = 396MHz */
    CCM->CBCDR &= ~(1 << 25);       /* periph_clk = pre_periph_clk = 396MHz */
    while(CCM->CDHIPR & (1 << 5));  /* 等待握手完成 */

    /**
     * 修改AHB_PODF位的时候需要先关闭AHB_CLK_ROOT时钟输出，但是
     * 并没有找到关闭AHB_CLK_ROOT输出的寄存器，无法设置。
     * 内部的Boot ROM会将AHB_PODF设置3分频，因此AHB_ROOT_CLK = 396MHz/3 = 132MHz
     * 下面代码仅供参考。
     */
#if 0
    /* 需要先关闭AHB_ROOT_CLK时钟输出 */
    CCM->CBCDR &= ~(7 << 10);   /* 将AHB_PODF位清0 */
    CCM->CBCDR |= (2 << 10);    /* AHB_PODF 3分频，AHB_CLK_ROOT = 132MHz */
#endif

    /* 5、设置IPG_CLK_ROOT时钟，最小为3MHz，最大为66MHz */
    CCM->CBCDR &= ~(3 << 8);    /* 将CCM_CBCDR的IPG_PODF清0 */
    CCM->CBCDR |= (1 << 8);     /* IPG_PODF 2分频，IPG_CLK_ROOT = 66MHz */

    /* 6、设置PERCLK_CLK_ROOT时钟 */
    CCM->CSCMR1 &= ~(1 << 6);   /* 设置PERCLK_CLK_ROOT时钟源为IPG */
    CCM->CSCMR1 &= ~(7 << 0);   /* PERCLK_PODF清0，1分频 */
}