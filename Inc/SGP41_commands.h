/*
 * SGP41_commands.h
 *
 *  Created on: Oct 22, 2024
 *      Author: riddick
 */

#ifndef SGP41_COMMANDS_H_
#define SGP41_COMMANDS_H_

#include <stdint.h>

/* ATTENTION: This instrument takes commands 2 bytes of length */


#define sgp41_execute_conditioning  ((uint16_t)0x2612)
#define sgp41_measure_raw_signals   ((uint16_t)0x2619)
#define sgp41_execute_self_test     ((uint16_t)0x280E)
#define sgp4x_turn_heater_off       ((uint16_t)0x3615)
#define sgp4x_get_serial_number     ((uint16_t)0x3682)


#endif /* SGP41_COMMANDS_H_ */
