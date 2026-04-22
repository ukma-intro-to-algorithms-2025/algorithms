#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef void* Item;
typedef struct Stack* StackPtr;

StackPtr StackInit(void);
int StackEmpty(StackPtr s);
size_t StackSize(StackPtr s); 
void push(StackPtr s, Item item);
Item pop(StackPtr s);
void StackDestroy(StackPtr s);

#endif