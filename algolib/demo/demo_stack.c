#include <stdio.h>
#include "../include/stack.h"

int main() {
    StackPtr stack = StackInit();
    
    printf("Testing Stack:\n");
    
    int values[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++) {
        push(stack, &values[i]);
        printf("Pushed: %d\n", values[i]);
    }
    
    printf("\nStack empty: %s\n", StackEmpty(stack) ? "yes" : "no");
    printf("Stack size: %zu\n", StackSize(stack));
    printf("\nPopping:\n");
    while (!StackEmpty(stack)) {
        int *val = (int*)pop(stack);
        printf("Popped: %d\n", *val);
    }
    
    printf("\nStack empty after popping: %s\n", StackEmpty(stack) ? "yes" : "no");
    
    StackDestroy(stack);
    return 0;
}