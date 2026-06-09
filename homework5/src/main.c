#include <stdio.h>
#include <stdlib.h>
#include "../include/hull.h"

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