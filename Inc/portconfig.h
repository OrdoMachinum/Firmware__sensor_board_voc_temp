/*
 * portconfig.h
 *
 *  Created on: Oct 7, 2024
 *      Author: riddick
 */

#ifndef PORTCONFIG_H_
#define PORTCONFIG_H_

#include "targetspec.h"


#define P_NRST_LED              (0u)    /* PortA-0  */

#define P_UART_RX               (14u)   /* PortC-14 */
#define P_UART_TX_SWCLK         (14u)   /* PortA-14 */

#define P_I2C_SDA               (10u)   /* PortA-10 */
#define P_I2C_SCL               (9u)    /* PortA-9  */
#define P_SWDIO                 (13u)   /* PortA-13 */



void init(void);

#endif /* PORTCONFIG_H_ */
