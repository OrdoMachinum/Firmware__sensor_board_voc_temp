/*
 * SHT4X_commands.h
 *
 *  Created on: Oct 19, 2024
 *      Author: riddick
 */

#ifndef SHT4X_COMMANDS_H_
#define SHT4X_COMMANDS_H_

#include <stdint.h>

#define SHT4X_M_TRH_HIPREC    ((uint8_t)0xFD) // measure T & RH with high precision (high repeatability) [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]
#define SHT4X_M_TRH_MEPREC    ((uint8_t)0xF6) // measure T & RH with medium precision (medium repeatability) [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]
#define SHT4X_M_TRH_LOPREC    ((uint8_t)0xE0) // measure T & RH with lowest precision (low repeatability) [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]

#define SHT4X_R_SERIAL        ((uint8_t)0x89) // read serial number [2 * 8-bit data; 8-bit CRC; 2 * 8-bit data; 8-bit CRC]

#define SHT4X_SOFT_RESER      ((uint8_t)0x94) // soft reset [ACK]

#define SHT4X_AH200_10        ((uint8_t)0x39) // activate heater with 200mW for 1s, including a high precision measurement just before deactivation [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]
#define SHT4X_AH200_01        ((uint8_t)0x32) // activate heater with 200mW for 0.1s, including a high precision measurement just before deactivation [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]
#define SHT4X_AH110_10        ((uint8_t)0x2F) // activate heater with 110mW for 1s, including a high precision measurement just before deactivation [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]
#define SHT4X_AH110_01        ((uint8_t)0x24) // activate heater with 110mW for 0.1s, including a high precision measurement just before deactivation [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]
#define SHT4X_AH020_10        ((uint8_t)0x1E) // activate heater with  20mW for 1s, including a high precision measurement just before deactivation [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]
#define SHT4X_AH020_01        ((uint8_t)0x15) // activate heater with  20mW for 0.1s, including a high precision measurement just before deactivation [2 * 8-bit T-data; 8-bit CRC; 2 * 8-bit RH-data; 8-bit CRC]

#endif /* SHT4X_COMMANDS_H_ */
