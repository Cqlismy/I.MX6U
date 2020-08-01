#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_gpio.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_epit.h"
#include "bsp_gptdelay.h"
#include "bsp_gptint.h"

/**
 * main() - 主函数
 */
int main(void)
{
    unsigned char led2_state = ON;

    interrupt_init();           /* 中断初始化 */
    imx6ul_clk_init();          /* 初始化相关时钟 */
    system_clk_enable();        /* 系统外设时钟使能 */
    delay_init();               /* 硬件定时器延时初始化 */
    led_init();                 /* LED灯初始化 */
    gpt2_init(66, 1000000);     /* EPIT1定时器初始化 */

    while (1) {
        led2_state = !led2_state;
        led_switch(LED2, led2_state);
        delay_ms(1000);
    }

    return 0;
}
