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

uint8_t I2C_write(
    const uint8_t devAdd,
    const uint8_t * buffer,
    uint16_t datLen)
{
    uint8_t byteWritten = 0u;
    uint32_t controlReg = (devAdd << 1u << I2C_CR2_SADD_Pos);
    controlReg |= datLen << I2C_CR2_NBYTES_Pos; // data bytes + register address
    controlReg |= 1u << I2C_CR2_START_Pos;

    I2C1->CR2 = controlReg;

    while (I2C1->CR2 & I2C_CR2_START) {
        /* Busy wait until Start, and device address are sent, so this bit is cleared by HW*/
    }

    if(I2C1->ISR & I2C_ISR_NACKF_Msk) {
        I2C1->ICR |= I2C_ICR_NACKCF;
        return byteWritten;
    }

    while (datLen--) {

        I2C1->TXDR = *buffer++;
        while (!(I2C1->ISR & I2C_ISR_TXE)) {
            /* wait until current byte is sent */
        }
        byteWritten++;
    }

    I2C1->CR2 |= I2C_CR2_STOP; /* Stop condition  */
    return byteWritten;
}

void I2C_writeReg(
    const uint8_t devAddr,
    const uint8_t devReg,
    const uint8_t * buffer,
    uint16_t datLen)
{
    uint32_t controlReg = (devAddr << 1u << I2C_CR2_SADD_Pos);
    controlReg |= (datLen + 1u) << I2C_CR2_NBYTES_Pos; /* data bytes +  1 register address byte*/
    controlReg |= 1u << I2C_CR2_START_Pos;

    I2C1->CR2 = controlReg;

    while (I2C1->CR2 & I2C_CR2_START) {
        /* Busy wait until Start, and device address are sent, so this bit is cleared by HW*/
    }

    if(I2C1->ISR & I2C_ISR_NACKF_Msk) {
        I2C1->ICR |= I2C_ICR_NACKCF;
        return;
    }

    I2C1->TXDR = devReg; /* Sending device register now */

    while (!(I2C1->ISR & I2C_ISR_TXE)) {
        /* wait until transmission is sent */
    }

    while (datLen--) {
        I2C1->TXDR = *buffer++;

        while (!(I2C1->ISR & I2C_ISR_TXE)) {
            /* wait until transmission is sent */
        }
    }
    I2C1->CR2 |= I2C_CR2_STOP; /* Stop condition  */
}


uint8_t I2C_read(
    const uint8_t devAddr,
    uint8_t * buffer,
    uint16_t datLen)
{
    uint32_t controlReg = (devAddr << 1u << I2C_CR2_SADD_Pos);
    uint8_t retVal = 0u;

    controlReg |= 1u << I2C_CR2_START_Pos;
    controlReg |= 1u << I2C_CR2_RD_WRN_Pos; /* We are reading */
    controlReg |= datLen << I2C_CR2_NBYTES_Pos; /* We are expecting so many bytes*/

    I2C1->CR2 = controlReg;

    while (I2C1->CR2 & I2C_CR2_START) {
        /* Busy wait until Start, and device address are sent, so this bit is cleared by HW*/
    }

    if(I2C1->ISR & I2C_ISR_NACKF_Msk) {
        return retVal;
    }

    while (datLen--)
    {
        while(!(I2C1->ISR & I2C_ISR_RXNE)) {
            /* Wait until there is something to read */
        }
        *buffer++ = I2C1->RXDR;
        retVal++;
    }
    I2C1->CR2 |= I2C_CR2_STOP;
    return retVal;
}

void I2C_readReg(
    const uint8_t devAddr,
    const uint8_t devReg,
    uint8_t * buffer,
    uint16_t datLen)
{
    uint32_t controlReg = (devAddr << 1u << I2C_CR2_SADD_Pos);
    controlReg |= 1u << I2C_CR2_NBYTES_Pos; // just the register address is sent first
    controlReg |= 1u << I2C_CR2_START_Pos;

    I2C1->CR2 = controlReg;

    while (I2C1->CR2 & I2C_CR2_START) {
        /* Busy wait until Start, and device address are sent, so this bit is cleared by HW*/
    }

    I2C1->TXDR = devReg;

    while (!(I2C1->ISR & I2C_ISR_TXE)) {
        /* wait until transmission is sent */
    }

    controlReg = I2C1->CR2;
    controlReg |= (devAddr << 1u << I2C_CR2_SADD_Pos);
    controlReg |= 1u << I2C_CR2_START_Pos;  /* we send a second start */
    controlReg |= 1u << I2C_CR2_RD_WRN_Pos; /* We are reading */
    controlReg |= datLen << I2C_CR2_NBYTES_Pos; /* We are expecting so many bytes*/

    I2C1->CR2 = controlReg;

    while (datLen--)
    {
        while(!(I2C1->ISR & I2C_ISR_RXNE)) {
            /* Wait until there is something to read */
        }
        *buffer++ = I2C1->RXDR;
    }
    I2C1->CR2 |= I2C_CR2_STOP;
}

