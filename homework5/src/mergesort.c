#include <stdio.h>
#include <stdlib.h>
#include "../include/sort.h"
#include "../include/point.h"

int compare_by_polar_angle(const void* p1, const void* p2, void* p0_ptr) {
    Point* a = (Point*)p1;
    Point* b = (Point*)p2;
    Point p0 = *(Point*)p0_ptr;
    double angleA = getAngle(p0, *a);
    double angleB = getAngle(p0, *b);
    if (angleA < angleB) return -1;
    if (angleA > angleB) return 1;
    int distA = (a->x - p0.x) * (a->x - p0.x) + (a->y - p0.y) * (a->y - p0.y);
    int distB = (b->x - p0.x) * (b->x - p0.x) + (b->y - p0.y) * (b->y - p0.y);
    return distA - distB;
}
static void merge(Point arr[], int l, int m, int r, Point p0) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Point* L = (Point*)malloc(n1 * sizeof(Point));
    Point* R = (Point*)malloc(n2 * sizeof(Point));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (compare_by_polar_angle(&L[i], &R[j], &p0) <= 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L);
    free(R);
}
void mergesort(Point arr[], int l, int r, Point p0) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort(arr, l, m, p0);
        mergesort(arr, m + 1, r, p0);
        merge(arr, l, m, r, p0);
    }
}