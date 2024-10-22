/**
 * Firmware for sensor-board-temp project
 */


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

bool    trhAvailable = false;
uint8_t trhTicksResult[6] = {
        /* initialization with default temp. and hum.
         * So it can be used as the initial compensation value for the SGP4x */
        0x80,
        0x00,
        0xA2,
        0x66,
        0x66,
        0x93};

uint8_t vocTicksResult[6] = {0};

void SysTick_Handler(void)
{
    msTick--;
    expired |= (!msTick);
}

int main(void)
{
    uint8_t recievedData, transmittedData;
    uint8_t buffer[10] = {0};

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

        case PreInit:
            if(expired){
                State = Init;
            }
            break;

        case Init:

            buffer[0] = MSB_OF2(sgp41_execute_conditioning);
            buffer[1] = LSB_OF2(sgp41_execute_conditioning);
            buffer[2] = trhTicksResult[0];
            buffer[3] = trhTicksResult[1];
            buffer[4] = trhTicksResult[2];
            buffer[5] = trhTicksResult[3];
            buffer[6] = trhTicksResult[4];
            buffer[7] = trhTicksResult[5];

            if(!I2C_write(I2C_ADDR_SGP41, buffer, 8u)) {
            //if(false) {
                State = Error;
            }else {
                msTick = 2500u;
                expired = false;

                State = HeatUp;
            }



            break;

        case HeatUp:
            UART1_transmit('_');
            if(expired){
                State = ReadyToMeasure;
                UART1_transmit('>');
            }


        case ReadyToMeasure:

            if('?'== recievedData ){

                buffer[0] = SHT4X_M_TRH_MEPREC;
                I2C_write(I2C_ADDR_SHT4X, buffer, 1u);

                buffer[0] = MSB_OF2(sgp41_measure_raw_signals);
                buffer[1] = LSB_OF2(sgp41_measure_raw_signals);

                //I2C_write(I2C_ADDR_SGP41, buffer, 2u);
                //I2C_write(I2C_ADDR_SGP41, trhTicksResult, 6u);

                msTick = 50u;
                expired = false;

                State = Measuring;
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

            I2C_read(I2C_ADDR_SHT4X, trhTicksResult, 6);
            //I2C_read(I2C_ADDR_SGP41, vocTicksResult, 6);

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
            State = ReadyToMeasure;
        }


    }
    return 1;
}



