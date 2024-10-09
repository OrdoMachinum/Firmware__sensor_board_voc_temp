/**
 * Firmware for sensor-board-temp project
 */

#include <stdint.h>


#include "stm32g0xx.h"
#include "portconfig.h"

void busyWait(volatile uint32_t timeDel)
{   /* Busy wait */
    volatile uint32_t n;
    while(timeDel--)
    {
        n = 1000u;
        while(n--);
    }
}
void init(void)
{
    RCC->IOPENR &= ~RCC_IOPENR_GPIOCEN_Msk;
    RCC->IOPENR |= RCC_IOPENR_GPIOCEN;

    GPIOC->MODER &= ~GPIO_MODER_MODE14_Msk;
    GPIOC->MODER |=  GPIO_MODER_MODE14_0;
}


int main(void)
{
    init();

    /* Loop forever */
    for(;;) {
        busyWait(400);
        GPIOC->BSRR = 1u << P_UART_RX;

        busyWait(400);
        GPIOC->BRR = 1u << P_UART_RX;

    }
}
