#include "bsp_led.h"

/**
 * led_init() - LED灯初始化函数
 * 
 * @return: 无
 */
void led_init(void)
{
    gpio_pin_config_t led1_config, led2_config;

    /* 设置CSI_DATA00引脚IO复用为GPIO4_IO21(LED1) */
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA00_GPIO4_IO21, 0);

    /* 设置CSI_DATA01引脚IO复用为GPIO4_IO22(LED2) */
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA01_GPIO4_IO22, 0);

    /**
     * 配置GPIO4_IO21和GPIO4_IO22引脚电气属性 
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
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA01_GPIO4_IO22, 0x10b0);

    /* 将LED1相关的GPIO方向设置为输出 */
    led1_config.direction = kGPIO_DigitalOutput;
    led1_config.value = 1;   /* 初始状态熄灭LED灯 */
    gpio_init(GPIO4, 21, &led1_config);

    /* 将LED2相关的GPIO方向设置为输出 */
    led2_config.direction = kGPIO_DigitalOutput;
    led2_config.value = 1;   /* 初始状态熄灭LED灯 */
    gpio_init(GPIO4, 22, &led2_config);
}

/**
 * led_switch() - LED灯状态设置
 * @led: 要控制的LED灯，LED1或者LED2
 * @status: ON->打开LED灯，OFF->关闭LED灯
 * 
 * @return: 无
 */
void led_switch(unsigned char led, unsigned char status)
{
    switch(led) {
        case LED1: /* LED1 */
            if (status == ON)
                gpio_pin_write(GPIO4, 21, 0);
            else
                gpio_pin_write(GPIO4, 21, 1);
            break;
        case LED2: /* LED2 */
            if (status == ON)
                gpio_pin_write(GPIO4, 22, 0);   /* 输出低电平点亮LED */
            else
                gpio_pin_write(GPIO4, 22, 1);   /* 输出高电平熄灭LED */
            break;
        default:
            return;
    }
}