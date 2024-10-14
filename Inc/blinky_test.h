/*
 * blinky_test.h
 *
 *  Created on: Oct 13, 2024
 *      Author: riddick
 */

#ifndef BLINKY_TEST_H_
#define BLINKY_TEST_H_

#include "stm32g0xx.h"


void busyWait(volatile uint32_t timeDel);

void initBlink(void);

void blink(void);



#endif /* BLINKY_TEST_H_ */
