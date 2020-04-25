#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
#include "bsp_led.h"
#include "bsp_key.h"

/**
 * main() - 主函数
 */
int main(void)
{
    int key_value = KEY_NONE;
    unsigned char led_state = OFF;

    system_clk_enable();   /* 外设时钟使能 */
    led_init();     /* LED灯初始化 */
    key_init();     /* 按键初始化 */

    while (1) {
        key_value = key_get_value();  /* 获取按键状态 */
        if (key_value == KEY0_VALUE) {
            led_state = !led_state;
            led_switch(led_state);
            key_value = KEY_NONE;
        }
        delay(10);
    }

    return 0;
}
