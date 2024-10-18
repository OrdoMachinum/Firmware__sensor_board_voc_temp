/*
 * portconfig.c
 *
 *  Created on: Oct 16, 2024
 *      Author: riddick
 */

#include "portconfig.h"

void init(void)
{

    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
#ifdef SBVT
    RCC->APBENR2 |=  RCC_APBENR2_USART1EN;
    RCC->APBENR1 |=  RCC_APBENR1_I2C1EN;
#else
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

#endif
}
