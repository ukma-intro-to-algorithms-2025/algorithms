#ifndef SORT_H
#define SORT_H

#include "point.h"

int compare_points(const void* p1, const void* p2);
int compare_by_polar_angle(const void* p1, const void* p2, void* p0_ptr);

void quicksort(Point arr[], int low, int high);
void mergesort(Point arr[], int l, int r, Point p0);

#endif