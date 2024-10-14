/**
 * Firmware for sensor-board-temp project
 */

#include <stdint.h>

#include "stm32g0xx.h"
#include "portconfig.h"
#include "queue.h"


#ifndef TEST_BLINKY

void init(void)
{
    RCC->IOPENR &= ~RCC_IOPENR_GPIOAEN_Msk;
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    RCC->IOPENR &= ~RCC_IOPENR_GPIOCEN_Msk;
    RCC->IOPENR |= RCC_IOPENR_GPIOCEN;

    RCC->APBENR2 &= ~RCC_APBENR2_USART1EN_Msk;
    RCC->APBENR2 |=  RCC_APBENR2_USART1EN;
}










#else
#include "blinky_test.h"
int main(void)
{
    initBlink();
    for(;;) {
        blink();
    }
}

#endif


