/*
 * General I2C library,
 * heavily inspired by Embedded Sw fundamentals by A. G. Dean
 */

#ifndef DRV_I2C_H_
#define DRV_I2C_H_

#include "targetspec.h"


void I2C_init(void);
void I2C_writeReg(const uint8_t devAddr, const uint8_t devReg, const uint8_t * buffer, const uint16_t datLen);
void I2C_readReg(const uint8_t devAddr, const uint8_t devReg, const uint8_t * buffer, const uint16_t datLen);
#endif /* DRV_I2C_H_ */
