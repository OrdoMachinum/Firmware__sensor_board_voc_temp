/*
 * blinky_test.c
 *
 *  Created on: Oct 13, 2024
 *      Author: riddick
 */
#include "blinky_test.h"

void busyWait(volatile uint32_t timeDel)
{   /* Busy wait */
    volatile uint32_t n;
    while(timeDel--)
    {
        n = 1000u;
        while(n--);
    }
}

void initBlink(void)
{

    RCC->IOPENR &= ~RCC_IOPENR_GPIOCEN_Msk;
    RCC->IOPENR |= RCC_IOPENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODE14_Msk;
    GPIOC->MODER |=  GPIO_MODER_MODE14_0;

}

void blink(void)
{
    busyWait(1400);
    GPIOC->BSRR = 1u << P_UART_RX;

    busyWait(400);
    GPIOC->BRR = 1u << P_UART_RX;
}

