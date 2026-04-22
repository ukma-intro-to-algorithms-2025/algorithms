#include <stdio.h>
#include "queue.h"

int main() {
    QueuePtr queue = QueueCreate();
    
    printf("Queue Demo (FIFO)\n\n");
    
    int values[] = {10, 20, 30, 40, 50};
    
    printf("Enqueuing elements:\n");
    for (int i = 0; i < 5; i++) {
        QueueEnqueue(queue, &values[i]);
        printf("  Enqueued: %d, Size: %zu\n", values[i], QueueSize(queue));
    }
    
    printf("\nQueue is empty: %s\n", QueueIsEmpty(queue) ? "yes" : "no");
    printf("Queue size: %zu\n", QueueSize(queue));
    
    printf("\nDequeuing elements (FIFO order):\n");
    while (!QueueIsEmpty(queue)) {
        int *val = (int*)QueueDequeue(queue);
        printf("  Dequeued: %d, Size: %zu\n", *val, QueueSize(queue));
    }
    
    printf("\nQueue is empty: %s\n", QueueIsEmpty(queue) ? "yes" : "no");
    
    QueueDestroy(queue);
    return 0;
}