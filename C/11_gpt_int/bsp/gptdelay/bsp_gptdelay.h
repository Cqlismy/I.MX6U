#ifndef __BSP_GTPDELAY_H
#define __BSP_GPTDELAY_H

#include "imx6ul.h"

void delay_init(void);
void delay_us(unsigned int us);
void delay_ms(unsigned int ms);

#endif