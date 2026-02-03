#ifndef STACK_H
#define STACK_H

typedef void* Item;
typedef struct Stack* StackPtr;

StackPtr StackInit();
int StackEmpty(StackPtr s);
void push(StackPtr s, Item item);
Item pop(StackPtr s);
void StackDestroy(StackPtr s);

#endif