/*
    Common header for target board specific includes, and definitions.
    The checked macros are defined in the relevant Eclipse project as
    symbols.
 */

#ifndef TARGETSPEC_H_
#define TARGETSPEC_H_

#include <stdint.h>


#if defined(STM32G030xx)    /* Target is on the original PCB */

#include "stm32g0xx.h"
#include "system_stm32g0xx.h"
#define SBVT
#define PERIPH_UART     USART1
#define TXE_MASK        USART_ISR_TXE_TXFNF
#define RXNE_MASK       USART_ISR_RXNE_RXFNE
#define I2C_TIMING_REG  0x00503D58

#elif defined(STM32L010xB)  /* Target is NUCLEO-L010RB board */

#include "stm32l0xx.h"
#include "system_stm32l0xx.h"
#define NUCLEO
#define PERIPH_UART     USART2
#define TXE_MASK        USART_ISR_TXE
#define RXNE_MASK       USART_ISR_RXNE

/* Considering 16MHz sysclock
 * Stanrard I2C mode
 * 100 kHz I2C freq.
 * 100 ns rise t.
 *  10 ns fall t. */
#define I2C_TIMING_REG  0x00503D5B

#else
#error "Target is not supported!"
#endif


#endif /* TARGETSPEC_H_ */
