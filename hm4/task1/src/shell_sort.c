#include "../include/sort.h"
#include <stdlib.h>
#include <string.h>

void shell_sort(void *base, size_t n, size_t size, cmp_func cmp){
    char *arr = (char *)base;
    for (size_t gap = n / 2; gap > 0; gap /= 2) { //зовн цикл ділення
        for (size_t i = gap; i < n; i++){ //вн цикл сортування підмасивів
            char *temp = malloc(size);
            memcpy(temp, arr + i * size, size);
            size_t j;
            for (j = i; j >= gap && cmp(arr + (j - gap) * size, temp) > 0; j -= gap) {  //порівняння та зсув елементів підмасиву
                memcpy(arr + j * size,  arr + (j - gap) * size,  size);
            }
            memcpy(arr + j * size, temp, size);
            free(temp);
        }
    }
}