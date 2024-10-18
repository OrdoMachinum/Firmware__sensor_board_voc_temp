/*
 * drv_i2c.c
 *
 *  Created on: Oct 16, 2024
 *      Author: riddick
 */


#include "drv_i2c.h"


void I2C_init(void)
{

#ifdef SBVT


    GPIOA->MODER &= ~GPIO_MODER_MODE9_Msk;
    GPIOA->MODER |=  GPIO_MODER_MODE9_1;

    GPIOA->MODER &= ~GPIO_MODER_MODE10_Msk;
    GPIOA->MODER |=  GPIO_MODER_MODE10_1;

    GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL9_Msk;
    GPIOA->AFR[1] |= 6u << GPIO_AFRH_AFSEL9_Pos;

    GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL10_Msk;
    GPIOA->AFR[1] |= 6u << GPIO_AFRH_AFSEL10_Pos;



#else

    GPIOB->MODER &= ~GPIO_MODER_MODE8_Msk;
    GPIOB->MODER |= GPIO_MODER_MODE8_1;

    GPIOB->MODER &= ~GPIO_MODER_MODE9_Msk;
    GPIOB->MODER |= GPIO_MODER_MODE9_1;

    GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL8_Msk;
    GPIOB->AFR[1] |= 4u << GPIO_AFRH_AFSEL8_Pos;

    GPIOB->AFR[1] &= ~GPIO_AFRH_AFSEL9_Msk;
    GPIOB->AFR[1] |= 4u << GPIO_AFRH_AFSEL9_Pos;

#endif
    I2C1->TIMINGR = I2C_TIMING_REG;
    I2C1->CR1 |= 1u << I2C_CR1_PE_Pos;
}

void I2C_writeReg(const uint8_t devAddr, const uint8_t devReg, const uint8_t * buffer, uint16_t datLen)
{
    uint32_t controlReg = (devAddr << 1u << I2C_CR2_SADD_Pos);
    controlReg |= (datLen + 1u) << I2C_CR2_NBYTES_Pos; // data bytes + register address
    controlReg |= 1u << I2C_CR2_START_Pos;

    I2C1->CR2 = controlReg;

    while (I2C1->CR2 & I2C_CR2_START) /* Busy wait until Start, and device address are sent, so this bit is cleared by HW*/
        ;

    I2C1->TXDR = devReg; /* Sending device register now */

    while (!(I2C1->ISR & I2C_ISR_TXE)) /* wait until transmission is sent */
        ;

    while (datLen--) {
        I2C1->TXDR = *buffer++;

        while (!(I2C1->ISR & I2C_ISR_TXE)) /* wait until transmission is sent */
                ;

    }

    I2C1->CR2 |= I2C_CR2_STOP; /* Stop condition  */
}


void I2C_readReg(const uint8_t devAddr, const uint8_t devReg, const uint8_t * buffer, const uint16_t datLen)
{

}

