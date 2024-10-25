/*
 * SGP41_commands.c
 *
 *  Created on: Oct 25, 2024
 *      Author: riddick
 */


#include "SGP41_commands.h"

uint8_t SGP41_conditioning(void)
{
    uint8_t buffer[] = {
            MSB_OF2(sgp41_execute_conditioning),
            LSB_OF2(sgp41_execute_conditioning),
            0x80,
            0x00,
            0xA2,
            0x66,
            0x66,
            0x93};

    return I2C_write(I2C_ADDR_SGP41, buffer, 8u);
}

uint8_t SGP41_startMeasure(
    uint8_t * buffer)
{
    buffer[0] = MSB_OF2(sgp41_measure_raw_signals);
    buffer[1] = LSB_OF2(sgp41_measure_raw_signals);

    return I2C_write(I2C_ADDR_SGP41, buffer, 8u);
}

uint8_t SGP41_getResults(
    uint8_t * buffer)
{
    return I2C_read(I2C_ADDR_SGP41, buffer, 6u);
}
