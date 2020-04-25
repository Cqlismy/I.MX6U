#include "bsp_gpio.h"

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
     * 配置GPIO1_IO08引脚电气属性 
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
 * gpio_output() - 控制GPIO的引脚电平
 * 
 * @param: 无
 * @return: 无
 */
void gpio_output(int status)
{
    if (status == hight)
        GPIO4->DR |= (1 << 21);
    else if (status == low)
        GPIO4->DR &= ~(1 << 21);
    else
        return;
}
