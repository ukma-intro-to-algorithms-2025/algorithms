#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "convex_hull.h"

#define PI 3.14159265358979323846

double getAngle(Point p0, Point p) {
    int dx = p.x - p0.x;
    int dy = p.y - p0.y;
    if (dx == 0 && dy == 0) return -1.0;
    return atan2(dy, dx);
}
int ccw(Point a, Point b, Point c) {
    int area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area2 > 0) return 1;
    if (area2 < 0) return -1;
    return 0;
}
int compare_points(const void* p1, const void* p2) {
    Point* a = (Point*)p1;
    Point* b = (Point*)p2;
    if (a->y == b->y) return a->x - b->x;
    return a->y - b->y;
}
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
void quick_sort_points(Point arr[], int low, int high) {
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
    quick_sort_points(arr, low, j);
    quick_sort_points(arr, i, high);
}
void merge(Point arr[], int l, int m, int r, Point p0) {
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
void merge_sort_points(Point arr[], int l, int r, Point p0) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_points(arr, l, m, p0);
        merge_sort_points(arr, m + 1, r, p0);
        merge(arr, l, m, r, p0);
    }
}
int convexHull(Point points[], int n, Point hull[]) {
    if (n < 3) {
        for (int i = 0; i < n; i++) hull[i] = points[i];
        return n;
    }
    quick_sort_points(points, 0, n - 1);
    Point p0 = points[0];
    merge_sort_points(points, 1, n - 1, p0);

    Point* stack = (Point*)malloc(n * sizeof(Point));
    int top = 0;
    stack[top++] = points[0];
    stack[top++] = points[1];

    for (int i = 2; i < n; i++) {
        while (top >= 2 && ccw(stack[top - 2], stack[top - 1], points[i]) <= 0) {
            top--;
        }
        stack[top++] = points[i];
    }
    for (int i = 0; i < top; i++) {
        hull[i] = stack[i];
    }
    free(stack);
    return top;
}
void drawPointsAndHull(Point points[], int n, Point hull[], int h) {
    if (n == 0) return;
    int minX = points[0].x, maxX = points[0].x;
    int minY = points[0].y, maxY = points[0].y;
    for (int i = 1; i < n; i++) {
        if (points[i].x < minX) minX = points[i].x;
        if (points[i].x > maxX) maxX = points[i].x;
        if (points[i].y < minY) minY = points[i].y;
        if (points[i].y > maxY) maxY = points[i].y;
    }
    int width = maxX - minX + 1;
    int height = maxY - minY + 1;

    if (width > 50 || height > 20) {
        printf("tooo big for ASCII\n");
        return;
    }
    char canvas[30][60];
    for (int y = 0; y < 30; y++)
        for (int x = 0; x < 60; x++)
            canvas[y][x] = ' ';
    for (int i = 0; i < n; i++) {
        int x = points[i].x - minX;
        int y = maxY - points[i].y;
        canvas[y][x * 2] = '.';
    }
    for (int i = 0; i < h; i++) {
        int x1 = hull[i].x - minX;
        int y1 = maxY - hull[i].y;
        int x2 = hull[(i + 1) % h].x - minX;
        int y2 = maxY - hull[(i + 1) % h].y;

        if (x1 == x2) {
            for (int y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++)
                canvas[y][x1 * 2] = '#';
        } else if (y1 == y2) {
            for (int x = (x1 < x2 ? x1 : x2) * 2; x <= (x1 > x2 ? x1 : x2) * 2; x++)
                canvas[y1][x] = '#';
        }
    }

    printf("\n");
    for (int y = 0; y <= maxY - minY; y++) {
        for (int x = 0; x <= (maxX - minX) * 2; x++) {
            printf("%c", canvas[y][x]);
        }
        printf("\n");
    }
}
int main() {
    printf("Convex Hull Algorithm (Graham Scan)\n");
    Point points[] = {{0, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}, {2, 0}};
    int n = sizeof(points) / sizeof(points[0]);
    printf("Original points:\n");
    for (int i = 0; i < n; i++) {
        printf("(%d,%d) ", points[i].x, points[i].y);
    }
    printf("\n\n");
    Point hull[100];
    int h = convexHull(points, n, hull);
    if (h > 0) {
        printf("Convex Hull (%d points):\n", h);
        for (int i = 0; i < h; i++) {
            printf("(%d,%d) ", hull[i].x, hull[i].y);
        }
        printf("\n\n");
        printf("ASCII Visualization:\n");
        drawPointsAndHull(points, n, hull, h);
    } else {
        printf("Not enough points for convex hull\n");
    }
    
    return 0;
}