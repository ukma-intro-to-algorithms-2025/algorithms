#ifndef QUEUE_H
#define QUEUE_H

#include "maze.h"
#include <stdbool.h>

typedef struct {
    pair_t *data;
    int head;
    int tail;
    int size;
    int capacity;
} Queue;

Queue* QueueCreate(int capacity);
void QueuePush(Queue *q, pair_t p);
pair_t QueuePop(Queue *q);
bool QueueIsEmpty(Queue *q);
void QueueDestroy(Queue *q);

#endif