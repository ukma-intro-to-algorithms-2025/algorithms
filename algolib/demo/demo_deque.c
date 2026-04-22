#include <stdio.h>
#include "deque.h"

int main() {
    DequePtr deque = DequeInit();
    
    printf("Deque Demo (Double-Ended Queue)\n\n");
    
    int values[] = {10, 20, 30, 40, 50};
    
    printf("Adding elements:\n");
    DequeAddLast(deque, &values[0]);
    printf("  AddLast(10), Size: %zu\n", DequeSize(deque));
    
    DequeAddLast(deque, &values[1]);
    printf("  AddLast(20), Size: %zu\n", DequeSize(deque));
    
    DequeAddFirst(deque, &values[2]);
    printf("  AddFirst(30), Size: %zu\n", DequeSize(deque));
    
    DequeAddLast(deque, &values[3]);
    printf("  AddLast(40), Size: %zu\n", DequeSize(deque));
    
    DequeAddFirst(deque, &values[4]);
    printf("  AddFirst(50), Size: %zu\n", DequeSize(deque));
    
    printf("\nCurrent size: %zu\n", DequeSize(deque));
    printf("Deque is empty: %s\n", DequeEmpty(deque) ? "yes" : "no");
    
    printf("\nRemoving from front (First):\n");
    while (!DequeEmpty(deque)) {
        int *val = (int*)DequeRemoveFirst(deque);
        printf("  RemovedFirst: %d, Size: %zu\n", *val, DequeSize(deque));
    }
    
    printf("\nRe-adding elements for RemoveLast demo:\n");
    for (int i = 0; i < 5; i++) {
        DequeAddLast(deque, &values[i]);
        printf("  AddLast(%d), Size: %zu\n", values[i], DequeSize(deque));
    }
    
    printf("\nRemoving from back (Last):\n");
    while (!DequeEmpty(deque)) {
        int *val = (int*)DequeRemoveLast(deque);
        printf("  RemovedLast: %d, Size: %zu\n", *val, DequeSize(deque));
    }
    
    printf("\nDeque is empty: %s\n", DequeEmpty(deque) ? "yes" : "no");
    
    DequeDestroy(deque);
    return 0;
}