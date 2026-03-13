#ifndef SORT_H
#define SORT_H

#include <stddef.h>

typedef int (*cmp_func)(const void *, const void *);

void insertion_sort(void *base, size_t n, size_t size, cmp_func cmp);
void selection_sort(void *base, size_t n, size_t size, cmp_func cmp);
void shell_sort(void *base, size_t n, size_t size, cmp_func cmp);

#endif
//size_t n - кількість елементів у масиві
//size_t size - розмір одного елемента в байтах
//cmp_func cmp - вказівник на функцію порівняння