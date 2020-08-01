#include "bsp_exit.h"
#include "bsp_gpio.h"
#include "bsp_int.h"
#include "bsp_delay.h"
#include "bsp_led.h"

/**
 * gpio_exit_init() - GPIO外部中断初始化
 * 
 * @param: 无
 * @return: 无
 */
void gpio_exit_init(void)
{
    gpio_pin_config_t key_config;

    /* 设置CSI_DATA02引脚IO口复用为GPIO4_IO23 */
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA02_GPIO4_IO23, 0);

    /**
     * 配置GPIO4_IO23引脚电气属性
     * bit[16]: 0 关闭HYS
     * bit[15:14]: 11 pull up 22k
     * bit[13]: 1 pull
     * bit[12]: 1 pull/keeper使能
     * bit[11]: 0 禁止开路输出
     * bit[10:8]: 000 resered
     * bit[7:6]: 10 速度为100MHz
     * bit[5:3]: 000 关闭输出
     * bit[2:1]: 00 resered
     * bit[0]: 0 低摆率
     */
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA02_GPIO4_IO23, 0xF080);

    /* 将按键相关的GPIO方向设置为输入，并配置中断 */
    key_config.direction = kGPIO_DigitalInput;
    key_config.interruptmode = kGPIO_IntFallingEdge;
    key_config.value = 1;
    gpio_init(GPIO4, 23, &key_config);

    /* 使能GIC中断控制器，注册GPIO中断服务函数并使能中断 */
    GIC_EnableIRQ(GPIO4_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO4_Combined_16_31_IRQn,
        (system_irq_handler_t)gpio4_io23_irqhander, NULL);
    gpio_enable_interrupt(GPIO4, 23);
}

/**
 * gpio4_io23_irqhander() - GPIO4_IO23中断服务处理函数
 * 
 * @giccIar: 中断号
 * @userParam: 用户参数
 * 
 * @return: 无
 */
void gpio4_io23_irqhander(unsigned int giccIar, void *userParam)
{
    static unsigned char led2_state = OFF;

    /**
     * 采用简单延时消抖，但是中断服务处理函数中
     * 禁止使用延时函数，因为中断服务处理需要快进
     * 快出。
     */
    delay(10);
    if (gpio_pin_read(GPIO4, 23) == 0) {
        led2_state = !led2_state;
        led_switch(LED2, led2_state);
    }

    gpio_clear_int_flags(GPIO4, 23); /* 清除GPIO4_IO23中断标志位 */
}