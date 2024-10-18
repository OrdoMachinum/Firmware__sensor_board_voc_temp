/*
 * drv_uart.h
 *
 *  Created on: Oct 13, 2024
 *      Author: riddick
 */

#ifndef DRV_UART_H_
#define DRV_UART_H_

#include "targetspec.h"
#include "portconfig.h"

#define F_USART_CLOCK   (SystemCoreClock)
#define BAUD_RATE       (9600UL)

void UART1_init(void);
void UART1_transmit(const uint8_t dataByte);
uint8_t UART1_receive(void);



#endif /* DRV_UART_H_ */