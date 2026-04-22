#include <stdio.h>
#include <assert.h>
#include "../include/stack.h"
#include "../include/queue.h"
#include "../include/deque.h"

int main() {
    printf("Running All Tests \n\n");
    
    printf("Testing Stack...\n");
    StackPtr s = StackInit();
    int a = 10, b = 20, c = 30;
    
    push(s, &a);
    push(s, &b);
    push(s, &c);
    
    assert(*(int*)pop(s) == 30);
    assert(*(int*)pop(s) == 20);
    assert(*(int*)pop(s) == 10);
    assert(StackEmpty(s));
    StackDestroy(s);
    printf("  Stack: PASS\n\n");
    
    printf("Testing Queue...\n");
    QueuePtr q = QueueCreate();
    int x = 1, y = 2, z = 3;
    
    QueueEnqueue(q, &x);
    QueueEnqueue(q, &y);
    QueueEnqueue(q, &z);
    
    assert(*(int*)QueueDequeue(q) == 1);
    assert(*(int*)QueueDequeue(q) == 2);
    assert(*(int*)QueueDequeue(q) == 3);
    assert(QueueIsEmpty(q));
    QueueDestroy(q);
    printf("  Queue: PASS\n\n");
    
    printf("Testing Deque...\n");
    DequePtr d = DequeInit();
    int p = 100, qq = 200, r = 300, sss = 400;
    
    printf("  Test 1: AddLast + RemoveFirst\n");
    DequeAddLast(d, &p);      
    DequeAddLast(d, &qq);    
    DequeAddLast(d, &r);    
    
    assert(*(int*)DequeRemoveFirst(d) == 100);
    assert(*(int*)DequeRemoveFirst(d) == 200);
    assert(*(int*)DequeRemoveFirst(d) == 300);
    assert(DequeEmpty(d));
    
    printf("  Test 2: AddFirst + RemoveLast\n");
    DequeAddFirst(d, &p);   
    DequeAddFirst(d, &qq);  
    DequeAddFirst(d, &r);     
    
    assert(*(int*)DequeRemoveLast(d) == 100);
    assert(*(int*)DequeRemoveLast(d) == 200);
    assert(*(int*)DequeRemoveLast(d) == 300);
    assert(DequeEmpty(d));
    
    printf("  Test 3: Mixed operations\n");
    DequeAddFirst(d, &p);   
    DequeAddLast(d, &qq);    
    DequeAddFirst(d, &r);     
    DequeAddLast(d, &sss);   
    
    assert(*(int*)DequeRemoveFirst(d) == 300);
    assert(*(int*)DequeRemoveLast(d) == 400);
    assert(*(int*)DequeRemoveFirst(d) == 100);
    assert(*(int*)DequeRemoveLast(d) == 200);
    assert(DequeEmpty(d));
    
    DequeDestroy(d);
    printf("  Deque: PASS\n\n");
    
    printf("Testing Size functions...\n");
    
    StackPtr s2 = StackInit();
    assert(StackEmpty(s2));
    StackDestroy(s2);
    
    QueuePtr q2 = QueueCreate();
    assert(QueueIsEmpty(q2));
    assert(QueueSize(q2) == 0);
    
    int val = 42;
    QueueEnqueue(q2, &val);
    assert(QueueSize(q2) == 1);
    QueueDequeue(q2);
    assert(QueueSize(q2) == 0);
    QueueDestroy(q2);
    
    DequePtr d2 = DequeInit();
    assert(DequeEmpty(d2));
    assert(DequeSize(d2) == 0);
    DequeAddFirst(d2, &val);
    assert(DequeSize(d2) == 1);
    DequeRemoveFirst(d2);
    assert(DequeSize(d2) == 0);
    DequeDestroy(d2);
    
    printf("  Size functions: PASS\n\n");

    return 0;
}