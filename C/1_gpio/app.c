#include "app.h"

/**
 * system_clk_enable() - 使能SoC上所有外设时钟 
 */
void system_clk_enable(void)
{
    CCM_CCGR0 = 0xffffffff;
    CCM_CCGR1 = 0xffffffff;
    CCM_CCGR2 = 0xffffffff;
    CCM_CCGR3 = 0xffffffff;
    CCM_CCGR4 = 0xffffffff;
    CCM_CCGR5 = 0xffffffff;
    CCM_CCGR6 = 0xffffffff;
}

/**
 * gpio_init() - 初始化控制的GPIO
 * 
 * @param: 无
 * @return: 无
 */
void gpio_init(void)
{
    /* 设置CSI_DATA00引脚IO复用为GPIO4_IO21 */
    SW_MUX_CTL_PAD_CSI_DATA00 = 0x5;

    /**
     * 配置GPIO4_IO21引脚电气属性 
     * bit[16]: 0 关闭HYS
     * bit[15:14]: 00 默认下拉
     * bit[13]: 0 keeper
     * bit[12]: 1 pull/keeper使能
     * bit[11]: 0 禁止开路输出
     * bit[10:8]: 000 reserved
     * bit[7:6]: 10 速度为100MHz
     * bit[5:3]: 110 驱动能力为R0/6
     * bit[2:1]: 00 reserved
     * bit[0]: 0 低摆率
     */
    SW_PAD_CTL_PAD_CSI_DATA00 = 0x10b0;

    /* 设置GPIO4_IO21的方向为输出 */
    GPIO4_GDIR = 0x00200000;

    /* 设置GPIO4_IO21引脚输出高电平 */
    GPIO4_DR = 0x00200000;
}

/**
 * gpio_output_low() - GPIO4_IO21输出低电平
 * 
 * @param: 无
 * @return: 无
 */
void gpio_output_low(void)
{
    GPIO4_DR &= ~(1 << 21);
}

/**
 * gpio_output_hight() - GPIO4_IO21输出高电平
 * 
 * @param: 无
 * @return: 无
 */
void gpio_output_hight(void)
{
    GPIO4_DR |= (1 << 21);
}

/**
 * delay_short() - 短时间延时函数
 * 
 * @n: 要循环的次数
 * 
 * @return: 无
 */
void delay_short(volatile unsigned int n)
{
    while(n--);
}

/**
 * delay() - 延时函数，SoC在396MHz大概延时1ms
 * 
 * @n: 要延时的ms数
 * 
 * @return: 无
 */
void delay(volatile unsigned int n)
{
    while(n--) {
        delay_short(0x07ff);
    }
}

/**
 * app() - 主函数
 */
void app(void)
{
    system_clk_enable();    /* 外设时钟使能 */
    gpio_init();            /* GPIO初始化 */

    while (1) {
        gpio_output_hight();
        delay(1000);
        gpio_output_low();
        delay(1000);
    }
}
