/*
 * SHT4X_commands.c
 *
 *  Created on: Oct 24, 2024
 *      Author: riddick
 */

#include "SHT4X_commands.h"


uint8_t SHT4x_startMeasure(
    uint8_t command)
{
    return I2C_write(I2C_ADDR_SHT4X, &command, 1u);
}

uint8_t SHT4X_getResults(
    uint8_t * resultBuffer)
{
    return I2C_read(I2C_ADDR_SHT4X, resultBuffer, 6u);
}
