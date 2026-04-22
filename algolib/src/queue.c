#include "../include/queue.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    Item item;
    struct Node* next;
} Node;

struct Queue {
    Node* head;
    Node* tail;
    size_t size;
};

QueuePtr QueueCreate(void) {
    QueuePtr q = malloc(sizeof(struct Queue));
    assert(q);
    q->head = q->tail = NULL;
    q->size = 0;
    return q;
}

void QueueEnqueue(QueuePtr q, Item item) {
    assert(q);
    Node* node = malloc(sizeof(Node));
    assert(node);
    node->item = item;
    node->next = NULL;
    
    if (q->tail) {
        q->tail->next = node;
    } else {
        q->head = node;
    }
    q->tail = node;
    q->size++;
}

Item QueueDequeue(QueuePtr q) {
    assert(q && q->size > 0);
    Node* node = q->head;
    Item item = node->item;
    q->head = node->next;
    if (!q->head) q->tail = NULL;
    free(node);
    q->size--;
    return item;
}

bool QueueIsEmpty(QueuePtr q) {
    assert(q);
    return q->size == 0;
}

size_t QueueSize(QueuePtr q) {
    assert(q);
    return q->size;
}

void QueueDestroy(QueuePtr q) {
    if (!q) return;
    while (!QueueIsEmpty(q)) {
        QueueDequeue(q);
    }
    free(q);
}