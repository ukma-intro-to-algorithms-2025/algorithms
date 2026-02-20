#ifndef DEQUE_H
#define DEQUE_H
#include <stddef.h>

typedef void* Item;

typedef struct Deque* DequePtr;
DequePtr DequeInit(); //двостороння черга
int DequeEmpty(DequePtr deque); 
size_t DequeSize(DequePtr deque); //кількість елементів та розмір 
void DequeAddFirst(DequePtr deque, Item item); 
void DequeAddLast(DequePtr deque, Item item);
Item DequeRemoveFirst(DequePtr deque); 
Item DequeRemoveLast(DequePtr deque);
void DequeDestroy(DequePtr deque);

#endif