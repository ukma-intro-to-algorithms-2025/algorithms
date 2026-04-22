#include "../include/stack.h"
#include <stdlib.h>
#include <stdio.h>

struct Node {
    Item item;
    struct Node *next;
};

struct Stack {
    struct Node *first;
    size_t size;  
};

StackPtr StackInit() {
    StackPtr s = malloc(sizeof(struct Stack));
    if (s) {
        s->first = NULL;
        s->size = 0;  
    }
    return s;
}

int StackEmpty(StackPtr s) {
    return s->first == NULL;
}

size_t StackSize(StackPtr s) {
    return s->size; 
}

void push(StackPtr s, Item item) {
    struct Node *newNode = malloc(sizeof(struct Node));
    if (!newNode) return;
    newNode->item = item;
    newNode->next = s->first;
    s->first = newNode;
    s->size++;  
}

Item pop(StackPtr s) {
    if (StackEmpty(s)) return NULL;
    Item item = s->first->item;
    struct Node *temp = s->first;
    s->first = s->first->next;
    free(temp);
    s->size--;
    return item;
}

void StackDestroy(StackPtr s) {
    while (!StackEmpty(s)) {
        pop(s);
    }
    free(s);
}