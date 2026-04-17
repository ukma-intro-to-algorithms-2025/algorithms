#include "queue.h"
#include <stdlib.h>

Queue* QueueCreate(int capacity) {
    Queue *q = malloc(sizeof(Queue));
    q->data = malloc(capacity * sizeof(pair_t));
    q->head = q->tail = q->size = 0;
    q->capacity = capacity;
    return q;
}

void QueuePush(Queue *q, pair_t p) {
    if (q->size < q->capacity) {
        q->data[q->tail] = p;
        q->tail = (q->tail + 1) % q->capacity;
        q->size++;
    }
}

pair_t QueuePop(Queue *q) {
    pair_t p = q->data[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return p;
}

bool QueueIsEmpty(Queue *q) {
    return q->size == 0;
}

void QueueDestroy(Queue *q) {
    free(q->data);
    free(q);
}