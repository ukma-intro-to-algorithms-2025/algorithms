#ifndef POINT_H  
#define POINT_H 

#include <stdio.h>   
#include <stdlib.h>   
#include <math.h>    
#include <float.h>    
#include <string.h> 

typedef struct Point {
    int x, y; 
} Point;

typedef Point* PointPtr;

PointPtr create_point(int x, int y);

void destroy_point(PointPtr p);

//порівняння точок спочатку за y, потім за x для сортування
int compare_points(const void* a, const void* b);

//обчислення нахилу між двома точками
double slope_to(PointPtr p1, PointPtr p2);

PointPtr* read_points_from_file(const char* filename, int* n);

void free_points_array(PointPtr* points, int n);

void print_collinear_line(PointPtr* line_points, int count);

void insertion_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*));

void selection_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*));

void shell_sort(void *base, size_t n, size_t size, int (*cmp)(const void*, const void*));

#endif