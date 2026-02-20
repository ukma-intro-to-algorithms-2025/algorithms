#include "randomized_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define INITIAL_CAPACITY 4

struct RandomizedQueue { 
    Item* data; //динамічний масив елементів
    size_t size; //кількість елементів у черзі
    size_t capacity; //ємність масиву
};
static void resize(RandomizedQueuePtr rq, size_t new_capacity) { //зміна розміру масиву
    Item* new_data = (Item*)malloc(new_capacity * sizeof(Item)); 
    assert(new_data);

    for (size_t i =0; i< rq->size;i++) { //копіювання старих даних у новий масив
        new_data[i] =rq->data[i];
    }

    free(rq->data); //звільнити старий масив
    rq->data=new_data; //встановити новий
    rq->capacity =new_capacity; //оновити ємність
} 
RandomizedQueuePtr RandomizedQueueInit() { //ініціалізація порожньої черги
    RandomizedQueuePtr rq= (RandomizedQueuePtr)malloc(sizeof(struct RandomizedQueue));
    assert(rq);
    rq->data = (Item*)malloc(INITIAL_CAPACITY * sizeof(Item));
    assert(rq->data);
    rq->size = 0; //початково 0 
    rq->capacity = INITIAL_CAPACITY;
    srand((unsigned)time(NULL)); 
    return rq;
}
bool RandomizedQueueEmpty(RandomizedQueuePtr rq) {
    assert(rq);
    return rq->size == 0; //порожня, якщо розмір 0
}
size_t RandomizedQueueSize(RandomizedQueuePtr rq) {
    assert(rq);
    return rq->size; //поточний розмір
} 
void RandomizedQueueEnqueue(RandomizedQueuePtr rq, Item item) {
    assert(rq);

    if (rq->size == rq->capacity) {
        resize(rq, rq->capacity * 2); //подвоїти ємність, якщо масив заповнений
    }
    rq->data[rq->size++] = item; //додати елемент і збільшити розмір
}
Item RandomizedQueueDequeue(RandomizedQueuePtr rq) { //видалення випадкового елемента
    assert(rq);
    assert(rq->size > 0);
    size_t index = rand() % rq->size; //випадковий індекс для видалення
    Item item = rq->data[index];
    rq->data[index] = rq->data[rq->size - 1]; //замінити видалений елемент останнім
    rq->size--;

    //зменшити масив якщо використовується 25% ємності
    if (rq->size > 0 && rq->size == rq->capacity / 4 && rq->capacity > INITIAL_CAPACITY) { 
        resize(rq, rq->capacity / 2); //зменшити ємність вдвічі
    }
    return item;
}
void RandomizedQueueDestroy(RandomizedQueuePtr rq) {
    if (!rq) return;
    free(rq->data);
    free(rq);
}
