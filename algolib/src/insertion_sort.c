#include "../include/sort.h"
#include <stdlib.h>
#include <string.h>

void insertion_sort(void *base, size_t n, size_t size, cmp_func cmp) {
    char *arr = (char *)base;
    for (size_t i = 1; i < n; i++) {  //поточний елемент 2
        char *key = malloc(size);
        memcpy(key, arr + i * size, size);
        int j = i - 1;
        while (j >= 0 && cmp(arr + j * size, key) > 0) { // рух від кінця відсотрованої до початку
            memcpy(arr + (j + 1) * size, arr + j * size, size); //зсув вправо, та перехід до попереднього 
                   j--; 
        }
        memcpy(arr + (j + 1) * size, key, size);
        free(key);
    }
}