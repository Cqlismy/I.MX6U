#include "bsp_key.h"

/**
 * key_init() - 按键初始化函数
 * 
 * @return: 无
 */
void key_init(void)
{
    gpio_pin_config_t key_config;

    /* 设置CSI_DATA02引脚IO口复用为GPIO4_IO23 */
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA02_GPIO4_IO23, 0);

    /* 配置GPIO4_IO23引脚电气属性 
     * bit [16]: 0 关闭HYS
     * bit [15:14]: 11 pull up 22k
     * bit [13]: 1 pull
     * bit [12]: 1 pull/keeper使能
     * bit [11]: 0 禁止开路输出
     * bit [10:8] 000 reserved
     * bit [7:6]: 10 速度为100MHz
     * bit [5:3]: 000 关闭输出
     * bit [0]: 0 低摆率
     */
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA02_GPIO4_IO23, 0xF080);

    /* 将按键相关的GPIO方向设置为输入 */
    key_config.direction = kGPIO_DigitalInput;
    gpio_init(GPIO4, 23, &key_config);
}

/**
 * key_get_value() - 获取按键的键值
 * 
 * @return: 0表示没有按键按下，1表示按键按下
 */
int key_get_value(void)
{
    int ret = KEY_NONE;
    static unsigned char release = 1; /* 表示按键处于释放状态 */

    if ((release == 1) && (gpio_pin_read(GPIO4, 23) == 0)) { /* 按键按下 */
        delay(10);
        if (gpio_pin_read(GPIO4, 23) == 0) {
            release = 0;
            ret = KEY0_VALUE;
        }
    } else if (gpio_pin_read(GPIO4, 23) == 1) { /* 按键未按下 */
        ret = KEY_NONE;
        release = 1; /* 标记按键处于释放状态 */
    }

    return ret;
}