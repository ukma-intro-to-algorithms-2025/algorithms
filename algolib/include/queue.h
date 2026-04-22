#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef void* Item;
typedef struct Queue* QueuePtr;

QueuePtr QueueCreate(void);
void QueueEnqueue(QueuePtr q, Item item);
Item QueueDequeue(QueuePtr q);
bool QueueIsEmpty(QueuePtr q);
size_t QueueSize(QueuePtr q);
void QueueDestroy(QueuePtr q);

#endif