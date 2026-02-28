#include "priority_queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*CompareFunc)(const void *a, const void *b);

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int compare_ints(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int compare_doubles(const void *a, const void *b) {
    double da = *(const double *)a;
    double db = *(const double *)b;
    return (da > db) - (da < db);
}

void generic_sink(void *base, int k, int N, size_t elem_size, CompareFunc cmp) {
    char *array = (char *)base;
    
    while (2 * k + 1 <= N - 1) {
        int j = 2 * k + 1;  
        
        if (j + 1 <= N - 1 && cmp(array + j * elem_size, array + (j + 1) * elem_size) < 0) {
            j++;
        }
        
        if (cmp(array + k * elem_size, array + j * elem_size) >= 0) {
            break;
        }
        
        char temp[elem_size];
        memcpy(temp, array + k * elem_size, elem_size);
        memcpy(array + k * elem_size, array + j * elem_size, elem_size);
        memcpy(array + j * elem_size, temp, elem_size);
        
        k = j;
    }
}

void generic_heapsort(void *base, size_t num_elements, size_t elem_size, CompareFunc cmp) {
    if (num_elements <= 1) return;
    
    char *array = (char *)base;
    int N = num_elements;
    
    for (int k = N / 2 - 1; k >= 0; k--) {
        generic_sink(array, k, N, elem_size, cmp);
    }
    
    while (N > 1) {
        char temp[elem_size];
        memcpy(temp, array, elem_size);
        memcpy(array, array + (N - 1) * elem_size, elem_size);
        memcpy(array + (N - 1) * elem_size, temp, elem_size);
        
        N--;
        generic_sink(array, 0, N, elem_size, cmp);
    }
}

int main() {
    printf("Testing generic heapsort with different data types:\n\n");
    
    {
        printf("Testing with strings:\n");
        char *str_arr[] = {"banana", "apple", "cherry", "date", "elderberry"};
        int N = sizeof(str_arr) / sizeof(str_arr[0]);
        
        printf("Original: ");
        for (int i = 0; i < N; i++) {
            printf("%s ", str_arr[i]);
        }
        printf("\n");
        
        generic_heapsort(str_arr, N, sizeof(char *), compare_strings);
        
        printf("Sorted:   ");
        for (int i = 0; i < N; i++) {
            printf("%s ", str_arr[i]);
        }
        printf("\n\n");
    }
    
    {
        printf("Testing with integers:\n");
        int int_arr[] = {64, 34, 25, 12, 22, 11, 90};
        int N = sizeof(int_arr) / sizeof(int_arr[0]);
        
        printf("Original: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", int_arr[i]);
        }
        printf("\n");
        
        generic_heapsort(int_arr, N, sizeof(int), compare_ints);
        
        printf("Sorted:   ");
        for (int i = 0; i < N; i++) {
            printf("%d ", int_arr[i]);
        }
        printf("\n\n");
    }
    
    {
        printf("Testing with doubles:\n");
        double double_arr[] = {3.14, 2.718, 1.618, 0.577, 2.236};
        int N = sizeof(double_arr) / sizeof(double_arr[0]);
        
        printf("Original: ");
        for (int i = 0; i < N; i++) {
            printf("%.3f ", double_arr[i]);
        }
        printf("\n");
        
        generic_heapsort(double_arr, N, sizeof(double), compare_doubles);
        
        printf("Sorted:   ");
        for (int i = 0; i < N; i++) {
            printf("%.3f ", double_arr[i]);
        }
        printf("\n");
    }
    
    return 0;
}