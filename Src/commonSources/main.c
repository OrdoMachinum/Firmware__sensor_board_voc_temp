/**
 * Firmware for sensor-board-temp project
 */


#include "targetspec.h"


#include "cmsis_gcc.h"
#include "portconfig.h"
#include "queue.h"
#include "drv_uart.h"


int main(void)
{
    uint8_t recievedData, transmittedData;

    SystemCoreClockUpdate();
    init();
    UART1_init();
    UART1_transmit('!');

    while(true) {
        recievedData = UART1_receive();
        transmittedData = recievedData+1;
        UART1_transmit(transmittedData);
        //UART1_transmit('a');

    }
    return 1;
}



