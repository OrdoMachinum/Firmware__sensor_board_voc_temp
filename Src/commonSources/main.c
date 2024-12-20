/**
 * Firmware for sensor-board-temp project
 */


#include <string.h>
#include "targetspec.h"


#include "cmsis_gcc.h"
#include "portconfig.h"
#include "queue.h"
#include "drv_uart.h"
#include "drv_i2c.h"
#include "SHT4X_commands.h"
#include "SGP41_commands.h"
#include "core_cm0plus.h"

typedef enum {
    PreInit,
    Init,
    HeatUp,
    ReadyToMeasure,
    Measuring,
    Finished,
    Error
}dtMeasFSM;

dtMeasFSM State = PreInit;

volatile uint32_t msTick = 300u;
volatile bool expired = false;

void SysTick_Handler(void)
{
    msTick--;
    expired |= (!msTick);
}

int main(void)
{
    bool    sgpPresent = true;
    bool    shtPresent = true;
    uint8_t recievedData = {0};
    uint8_t buffer [14u] = {
            0x00,   /* Reserved for SGP4 command bytes */
            0x00,   /* Reserved for SGP4 command bytes */
            /* initialization with default temp. and hum.
             * So it can be used as the initial compensation value for the SGP4x */
            0x80,
            0x00,
            0xA2,
            0x66,
            0x66,
            0x93,
    };
    uint8_t * trhTicksResult = buffer+2u;
    uint8_t * vocTicksResult = buffer+8u;

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);

    init();
    UART1_init();
    I2C_init();
    UART1_transmit('o');
    UART1_transmit('k');

    while(true) {

        recievedData = UART1_receiveAsync();

        switch(State) {
        case PreInit: /* Wait for everything to power up */
            if(expired){
                State = Init;
            }
            break;

        case Init:  //State = ReadyToMeasure; break; // to bypass SGP init if needed
            sgpPresent = SGP41_conditioning();
            if(sgpPresent){
                msTick = 2500u;
                expired = false;
                State = HeatUp;
            } else {
                State = ReadyToMeasure;
            }
            break;

        case HeatUp:
            if(expired){
                State = ReadyToMeasure;
                UART1_transmit('>');
            }
            break;

        case ReadyToMeasure:
            if ('?' == recievedData) {
                shtPresent = SHT4x_startMeasure(SHT4X_M_TRH_HIPREC);

                if(sgpPresent) {
                    SGP41_startMeasure(buffer);
                }

                if(!sgpPresent && !shtPresent){
                    State = Error;
                } else {
                    msTick = 80u;
                    expired = false;
                    State = Measuring;
                }
            }
            break;

        case Measuring:
            UART1_transmit('.');
            if(expired) {
                State = Finished;
                UART1_transmit('>');
            }
            break;

        case Finished:
            if(shtPresent){
                SHT4X_getResults(trhTicksResult);
            }
            if(sgpPresent){
                SGP41_getResults(vocTicksResult);
            }

            UART1_transmit(trhTicksResult[0]);
            UART1_transmit(trhTicksResult[1]);
            UART1_transmit(trhTicksResult[3]);
            UART1_transmit(trhTicksResult[4]);

            UART1_transmit(vocTicksResult[0]);
            UART1_transmit(vocTicksResult[1]);
            UART1_transmit(vocTicksResult[3]);
            UART1_transmit(vocTicksResult[4]);

            UART1_transmit('\n');

            State = ReadyToMeasure;
            break;

        default:
        case Error:
            UART1_transmit('X');
//            State = ReadyToMeasure;
            break;
        }
    }
    return 1;
}



