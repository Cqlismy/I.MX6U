#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exit.h"

/**
 * main() - 主函数
 */
int main(void)
{
    unsigned char led1_state = OFF;

    interrupt_init();       /* 中断初始化 */
    imx6ul_clk_init();      /* 初始化相关时钟 */
    system_clk_enable();    /* 系统外设时钟使能 */
    led_init();             /* LED灯初始化 */
    gpio_exit_init();       /* GPIO外部中断初始化 */

    while (1) {
        led1_state = !led1_state;
        led_switch(LED1, led1_state);
        delay(500);
    }

    return 0;
}
