#include <stdio.h>
#include <stdlib.h>
#include "../include/hull.h"
#include "../include/sort.h"

int convexHull(Point points[], int n, Point hull[]) {
    if (n < 3) {
        for (int i = 0; i < n; i++) hull[i] = points[i];
        return n;
    }
    quicksort(points, 0, n - 1);
    Point p0 = points[0];
    mergesort(points, 1, n - 1, p0);
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
    if (maxX - minX > 50 || maxY - minY > 20) {
        printf("tooo big for ASCII\n");
        return;
    }
    char canvas[30][60];
    for (int y = 0; y < 30; y++)
        for (int x = 0; x < 60; x++)
            canvas[y][x] = ' ';

    for (int i = 0; i < n; i++) {
        int x = (points[i].x - minX) * 2;
        int y = maxY - points[i].y;
        canvas[y][x] = '.';
    }
    for (int i = 0; i < h; i++) {
        int x1 = (hull[i].x - minX) * 2;
        int y1 = maxY - hull[i].y;
        int x2 = (hull[(i + 1) % h].x - minX) * 2;
        int y2 = maxY - hull[(i + 1) % h].y;
        if (y1 == y2) {
            for (int x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++)
                canvas[y1][x] = '#';
        }
    }
    for (int y = 0; y <= maxY - minY; y++) {
        for (int x = 0; x <= (maxX - minX) * 2; x++) {
            printf("%c", canvas[y][x]);
        }
        printf("\n");
    }
}