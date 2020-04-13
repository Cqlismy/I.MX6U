#include "bsp_gpio.h"

/**
 * gpio_init() - 初始化控制的GPIO 
 */
void gpio_init(void)
{
    /* 设置IO口复用模式为GPIO */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08, 0);

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
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08, 0x10b0);

    /* 设置GPIO的方向为输出 */
    GPIO1->GDIR |= (1 << 8);

    /* 设置GPIO1_IO08引脚输出高电平 */
    GPIO1->DR |= (1 << 8);
}

/**
 * gpio_output() - 控制GPIO的引脚电平 
 */
void gpio_output(int status)
{
    if (status == hight)
        GPIO1->DR |= (1 << 8);
    else if (status == low)
        GPIO1->DR &= ~(1 << 8);
    else
        return;
    
}
