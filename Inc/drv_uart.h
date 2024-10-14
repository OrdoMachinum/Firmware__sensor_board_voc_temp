/*
 * drv_uart.h
 *
 *  Created on: Oct 13, 2024
 *      Author: riddick
 */

#ifndef DRV_UART_H_
#define DRV_UART_H_

#include <stdint.h>

void UART1_init(void);
void UART1_transmit(uint8_t dataByte);
uint8_t UART1_receive(void);



#endif /* DRV_UART_H_ */
