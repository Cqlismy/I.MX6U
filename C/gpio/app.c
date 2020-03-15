#include "app.h"

/**
 * clk_enable() - 使能SoC上所有外设时钟 
 */
void clk_enable(void)
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
 */
void gpio_init(void)
{
    /* 设置IO口复用模式为GPIO */
    SW_MUX_CTL_PAD_GPIO1_IO08 = 0x5;

    /* 配置GPIO1_IO08引脚电气属性 
     * bit [16]: 0 关闭HYS
     * bit [15:14]: 00 默认下拉
     * bit [13]: 0 keeper
     * bit [12]: 1 pull/keeper使能
     * bit [11]: 0 禁止开路输出
     * bit [7:6]: 10 速度为100MHz
     * bit [5:3]: 110 驱动能力为R0/6
     * bit [0]: 0 低摆率
     */
    SW_PAD_CTL_PAD_GPIO1_IO08 = 0x10b0;

    /* 设置GPIO的方向为输出 */
    GPIO1_GDIR = 0x00000100;

    /* 设置GPIO1_IO08引脚输出高电平 */
    GPIO1_DR = 0x00000100;
}

/**
 * gpio_output_low() - GPIO1_IO08输出低电平 
 */
void gpio_output_low(void)
{
    GPIO1_DR &= ~(0x1 << 8);
}

/**
 * gpio_output_hight() - GPIO1_IO08输出高电平 
 */
void gpio_output_hight(void)
{
    GPIO1_DR |= (0x1 << 8);
}

/**
 * delay_short() - 短时间延时函数
 * 
 * @n: 要循环的次数
 */
void delay_short(volatile unsigned int n)
{
    while(n--);
}

/**
 * delay() - 延时函数，SoC在396MHz大概延时1ms
 * 
 * @n: 要延时的ms数
 */
void delay(volatile unsigned int n)
{
    while(n--) {
        delay_short(0x07ff);
    }
}

/**
 * myapp() - 主函数
 */
void myapp(void)
{
    clk_enable();   /* 外设时钟使能 */
    gpio_init();    /* GPIO初始化 */

    while (1) {
        gpio_output_hight();
        delay(1000);
        gpio_output_low();
        delay(1000);
    }
}
