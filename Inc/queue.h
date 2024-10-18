/*
 * General Queue library
 * heavily inspired by Embedded Sw fundamentals by A. G. Dean
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>
#include <stdbool.h>
#include "cmsis_gcc.h"

#define Q_MAX_SIZE (256u)

typedef struct dtQueue_tag {
    uint8_t Data[Q_MAX_SIZE];
    unsigned int Head;          // Oldest data element's Index
    unsigned int Tail;          // Index of next Free space in array
    unsigned int Size;          // Element number in array
} dtQueue;

int qEnQueue(dtQueue * const q, const uint8_t dataB);
uint8_t qDeQueue(dtQueue * const q);

void qInit(dtQueue * const q);
bool qIsEmpty(const dtQueue * const q);
bool qIsFull(const dtQueue * const q);

unsigned int qSize(const dtQueue * const q);

#endif /* QUEUE_H_ */
