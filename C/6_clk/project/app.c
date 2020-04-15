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
    int cnt = 0;
    unsigned char led1_state = OFF;
    unsigned char led2_state = OFF;

    clk_enable();   /* 外设时钟使能 */
    led_init();     /* LED灯初始化 */
    key_init();     /* 按键初始化 */

    while (1) {
        key_value = key_get_value();  /* 获取按键状态 */
        if (key_value == KEY0_VALUE) {
            led1_state = !led1_state;
            led_switch(LED2, led1_state);
            key_value = KEY_NONE;
        }

        cnt++;
        if (cnt == 100) {   /* LED灯提示系统在运行 */
            led2_state = !led2_state;
            led_switch(LED1, led2_state);
            cnt = 0;
        }

        delay(10);
    }

    return 0;
}
