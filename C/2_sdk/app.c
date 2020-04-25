#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6G2.h"

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
 * gpio_init() - 初始化控制的GPIO
 * 
 * @param: 无
 * @return: 无
 */
void gpio_init(void)
{
    /* 设置CSI_DATA00引脚IO复用为GPIO4_IO21 */
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA00_GPIO4_IO21, 0);

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
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA00_GPIO4_IO21, 0x10b0);

    /* 设置GPIO的方向为输出 */
    GPIO4->GDIR |= (1 << 21);

    /* 设置GPIO1_IO08引脚输出高电平 */
    GPIO4->DR |= (1 << 21);
}

/**
 * gpio_output_low() - GPIO1_IO08输出低电平
 * 
 * @param: 无
 * @return: 无
 */
void gpio_output_low(void)
{
    GPIO4->DR &= ~(1 << 21);
}

/**
 * gpio_output_hight() - GPIO1_IO08输出高电平
 * 
 * @param: 无
 * @return: 无
 */
void gpio_output_hight(void)
{
    GPIO4->DR |= (1 << 21);
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
    system_clk_enable();   /* 外设时钟使能 */
    gpio_init();    /* GPIO初始化 */

    while (1) {
        gpio_output_hight();
        delay(1000);
        gpio_output_low();
        delay(1000);
    }
}
