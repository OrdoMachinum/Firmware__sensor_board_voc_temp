/*
 * drv_uart.c
 *
 *  Created on: Oct 16, 2024
 *      Author: riddick
 */
#include"drv_uart.h"

void UART1_init(void)
{
#ifdef SBVT
    GPIOB->MODER &= ~GPIO_MODER_MODE6_Msk;
    GPIOB->MODER |= GPIO_MODER_MODE6_1;

    GPIOB->MODER &= ~GPIO_MODER_MODE7_Msk;
    GPIOB->MODER |= GPIO_MODER_MODE7_1;

    /* Explicit pin AFR setting is not needed since the reset values
     * are good for us in the GPIOB_AFRL
     * PB6 to UART_TX
     * PB7 to UART_RX */

#else

    GPIOA->MODER &= ~GPIO_MODER_MODE2_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE2_1;

    GPIOA->MODER &= ~GPIO_MODER_MODE3_Msk;
    GPIOA->MODER |= GPIO_MODER_MODE3_1;

    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL2_Msk;
    GPIOA->AFR[0] |= (1u<<2u) << GPIO_AFRL_AFSEL2_Pos;

    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL3_Msk;
    GPIOA->AFR[0] |= (1u<<2u) << GPIO_AFRL_AFSEL3_Pos;
#endif

    PERIPH_UART->BRR = F_USART_CLOCK / BAUD_RATE;

    /* Default settings in CR are good for now for STLINK-usb communication:
     * No Parity,
     * 8 data bit,
     * 1 Stop bit  */

    /* Enabling */
    PERIPH_UART->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE;
}

void UART1_transmit(const uint8_t dataByte)
{
    while(! (PERIPH_UART->ISR & TXE_MASK)) /* Busy wait for not-full (or empty) TX fifo*/
        ;
    PERIPH_UART->TDR = dataByte;
}

uint8_t UART1_receive(void)
{
    while (! (PERIPH_UART->ISR & RXNE_MASK)) /* Busy wait fot not-empty (or full) RX Fifo */
        ;
    return PERIPH_UART->RDR;
}
