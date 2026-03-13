#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/sort.h"

int int_cmp(const void *a, const void *b){
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}
void fill_random(int *arr, size_t n){
    for (size_t i = 0; i < n; i++)
        arr[i] = rand();
}
void fill_sorted(int *arr, size_t n){
    for (size_t i = 0; i < n; i++)
        arr[i] = i;
}
double measure(void (*sort_func)(void *, size_t, size_t, cmp_func),
               int *arr, size_t n){
    clock_t start = clock();
    sort_func(arr, n, sizeof(int), int_cmp);
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}
int main(){
    size_t sizes[] = {100, 1000, 10000, 100000};
    int tests = 4;
    printf("Size | Insertion | Selection | Shell | Sorted Insertion | Sorted Selection | Sorted Shell\n");

    for (int i = 0; i < tests; i++){
        size_t n = sizes[i];
        int *arr1 = malloc(n * sizeof(int));
        int *arr2 = malloc(n * sizeof(int));
        int *arr3 = malloc(n * sizeof(int));
        fill_random(arr1, n); 
        memcpy(arr2, arr1, n * sizeof(int));
        memcpy(arr3, arr1, n * sizeof(int));
        double t1 = measure(insertion_sort, arr1, n);
        double t2 = measure(selection_sort, arr2, n);
        double t3 = measure(shell_sort, arr3, n);
        fill_sorted(arr1, n);
        fill_sorted(arr2, n);
        fill_sorted(arr3, n);
        double ts1 = measure(insertion_sort, arr1, n);
        double ts2 = measure(selection_sort, arr2, n);
        double ts3 = measure(shell_sort, arr3, n);
        printf("%5zu | %9f | %9f | %6f | %16f | %16f | %12f\n",
               n, t1, t2, t3, ts1, ts2, ts3);
        free(arr1);
        free(arr2);
        free(arr3);
    }
    return 0;
}