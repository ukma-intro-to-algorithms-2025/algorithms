#include "deque.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Node { //внутрішній вузол двосторонньої черги
    Item data; //вузол зберігає вказівник на дані
    struct Node* next;  //наступний вузол
    struct Node* prev;  //попередній вузол
} Node;
struct Deque { 
    Node* head; //перший елемент
    Node* tail; //останній елемент
    size_t size; 
};
DequePtr DequeInit() {   //нова порожня двостороння черга
    DequePtr deque=(DequePtr)malloc(sizeof(struct Deque));
    assert(deque);
    deque->head =NULL;  
    deque->tail= NULL; 
    deque->size = 0;    
    return deque;
}
int DequeEmpty(DequePtr deque) {
    assert(deque);
    return deque->size==0;
}
size_t DequeSize(DequePtr deque) { //кількість елементів у черзі
    assert(deque);
    return deque->size;  
}
void DequeAddFirst(DequePtr deque,Item item) {
    assert(deque);

    Node* node = (Node*)malloc(sizeof(Node)); // створення нового вузла
    assert(node); 
    node->data =item; //заповнення даних вузла
    node->prev=NULL;  //вузол стає першим, тому попереднього немає
    node->next=deque->head; //вузол вказує на колишній перший вузол

    if (deque->head)  //якщо не порожня черга
        deque->head->prev = node;  //минулий перший вказує на новий попередній
    else //якщо порожня то новий вузол є першим і останнім
        deque->tail =node;

    deque->head= node; //новий вузол стає першим
    deque->size++; 
}
void DequeAddLast(DequePtr deque,Item item) {
    assert(deque);
    Node* node = (Node*)malloc(sizeof(Node));
    assert(node);

    node->data =item;
    node->next=NULL; //останній, тому наступного немає
    node->prev =deque->tail;

    if (deque->tail)
        deque->tail->next=node; 
    else
        deque->head=node;

    deque->tail= node;
    deque->size++;
}
Item DequeRemoveFirst(DequePtr deque) {
    assert(deque);
    assert(deque->size> 0);

    Node* node=deque->head; //збереження вузла на видалення
    Item item= node->data; //збереження даних для повернення

    deque->head = node->next; //новий перший вузол
    if (deque->head)
        deque->head->prev =NULL;  //новий перший не має попереднього
    else
        deque->tail=NULL; 

    free(node);
    deque->size--;
    return item;
}
Item DequeRemoveLast(DequePtr deque) {
    assert(deque);
    assert(deque->size > 0);

    Node* node =deque->tail;
    Item item=node->data;
    deque->tail = node->prev;
    if (deque->tail) //якщо не порожня після видалення
        deque->tail->next=NULL; //новий останній не має наступного
    else
        deque->head= NULL;

    free(node);
    deque->size--;
    return item;
}
void DequeDestroy(DequePtr deque) {
    if (!deque) return;
    Node*cur =deque->head;
    while (cur) {
        Node* next =cur->next;
        free(cur);
        cur =next;
    }
    free(deque);
}
