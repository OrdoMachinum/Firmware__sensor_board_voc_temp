/*
 * queue.c
 *
 *  Created on: Oct 11, 2024
 *      Author: riddick
 */
#include "queue.h"


void qInit(
    dtQueue * const q)
{
    for(unsigned int i = 0u; i < Q_MAX_SIZE; ++i){
        q->Data[i] = 0x0u;
    }
    q->Head = 0u;
    q->Tail = 0u;
    q->Size = 0u;
}


/**
 * Append q queue at tail with content of dataB
 * @param q Queue
 * @param dataB byte to be written into the queue
 * @return 0 if error, 1 if ok
 */
int qEnQueue(
    dtQueue * const q,
    const uint8_t dataB)
{
    int retVal = 0;

    if(!qIsFull(q)) {

        uint32_t iMaskState = __get_PRIMASK();
        __disable_irq();

        q->Data[q->Tail] = dataB;
        q->Tail = (q->Tail + 1u) % Q_MAX_SIZE;
        q->Size++;

        retVal = 1;

        __set_PRIMASK(iMaskState);
        __enable_irq();
    }
    return retVal;
}
/**
 * Returns data byte at the head of queue
 * @param q Queue
 * @return data byte
 */
uint8_t qDeQueue(
    dtQueue * const q)
{
    uint8_t retData = 0x0u;

    if(!qIsEmpty(q)) {

        uint32_t iMaskState = __get_PRIMASK();
        __disable_irq();

        retData = q->Data[q->Head];
        q->Data[q->Head] = '_'; // For dbug of queue
        q->Head = (q->Head + 1u) % Q_MAX_SIZE;
        q->Size--;

        __set_PRIMASK(iMaskState);
        __enable_irq();
    }

    return retData;
}


bool qIsEmpty(const dtQueue * const q)
{
    return q->Size == 0u;
}
bool qIsFull(const dtQueue * const q)
{
    return q->Size >= Q_MAX_SIZE;
}

unsigned int qSize(const dtQueue * const q)
{
    return q->Size;
}
