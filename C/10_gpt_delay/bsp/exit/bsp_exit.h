#ifndef __BSP_EXIT_H
#define __BSP_EXIT_H

#include "imx6ul.h"

void gpio_exit_init(void);
void gpio4_io23_irqhander(unsigned int giccIar, void *userParam);

#endif