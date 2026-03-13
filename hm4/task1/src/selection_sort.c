#include "../include/sort.h"
#include <stdlib.h>
#include <string.h>

static void swap(void *a, void *b, size_t size){
    char *tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}
void selection_sort(void *base, size_t n, size_t size, cmp_func cmp){
    char *arr = (char *)base;
    for (size_t i = 0; i < n - 1; i++){ //зовнішній - item
        size_t min = i;
        for (size_t j = i + 1; j < n; j++) { //внутрішній - minimum
            if (cmp(arr + j * size, arr + min * size) < 0)  //
                min = j;
           }
        if (min != i)   
            swap(arr + i * size, arr + min * size, size); //змінення позицій minimum
    }
}