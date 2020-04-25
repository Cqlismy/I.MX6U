#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
#include "bsp_led.h"

/**
 * main() - 主函数
 */
int main(void)
{
    system_clk_enable();    /* 外设时钟使能 */
    led_init();             /* LED灯初始化 */

    while (1) {
        led_output(LED_ON);
        delay(1000);
        led_output(LED_OFF);
        delay(1000);
    }

    return 0;
}
