#ifndef SORT_H
#define SORT_H

#include <stddef.h>
#include "point.h"

typedef int (*cmp_func)(const void *, const void *);

void insertion_sort(void *base, size_t n, size_t size, cmp_func cmp);
void selection_sort(void *base, size_t n, size_t size, cmp_func cmp);
void shell_sort(void *base, size_t n, size_t size, cmp_func cmp);

void quicksort_points(Point arr[], int low, int high);
void mergesort_points(Point arr[], int l, int r, Point p0);

#endif