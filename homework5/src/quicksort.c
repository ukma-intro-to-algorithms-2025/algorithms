#include <stdio.h>
#include <stdlib.h>
#include "../include/sort.h"

int compare_points(const void* p1, const void* p2) {
    Point* a = (Point*)p1;
    Point* b = (Point*)p2;
    if (a->y == b->y) return a->x - b->x;
    return a->y - b->y;
}
void quicksort(Point arr[], int low, int high) {
    if (low >= high) return;
    int i = low, j = high;
    Point pivot = arr[(low + high) / 2];
    while (i <= j) {
        while (compare_points(&arr[i], &pivot) < 0) i++;
        while (compare_points(&arr[j], &pivot) > 0) j--;
        
        if (i <= j) {
            Point temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++; j--;
        }
    }
    quicksort(arr, low, j);
    quicksort(arr, i, high);
}