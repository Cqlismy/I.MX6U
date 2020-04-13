#include "bsp_led.h"

/**
 * led_init() - 初始化控制的LED灯
 */
void led_init(void)
{
    /* 设置IO口复用模式为GPIO */
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA00_GPIO4_IO21, 0);

    /* 配置GPIO4_IO21引脚电气属性 
     * bit [16]: 0 关闭HYS
     * bit [15:14]: 00 默认下拉
     * bit [13]: 0 keeper
     * bit [12]: 1 pull/keeper使能
     * bit [11]: 0 禁止开路输出
     * bit [7:6]: 10 速度为100MHz
     * bit [5:3]: 110 驱动能力为R0/6
     * bit [0]: 0 低摆率
     */
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA00_GPIO4_IO21, 0x10b0);

    /* 设置GPIO的方向为输出 */
    GPIO4->GDIR |= (1 << 21);

    /* 设置GPIO1_IO08引脚输出高电平 */
    GPIO4->DR |= (1 << 21);
}

/**
 * gpio_output() - 控制LED灯的亮灭
 * 
 * @status: LED_ON为点亮，LED_OFF为熄灭 
 */
void led_output(int status)
{
    if (status == LED_OFF)
        GPIO4->DR |= (1 << 21);
    else if (status == LED_ON)
        GPIO4->DR &= ~(1 << 21);
    else
        return;
    
}
