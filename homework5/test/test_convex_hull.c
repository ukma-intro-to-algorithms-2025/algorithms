#include <stdio.h>
#include <assert.h>
#include "../include/hull.h"

void printHull(Point hull[], int h) {
    for (int i = 0; i < h; i++) {
        printf("(%d,%d) ", hull[i].x, hull[i].y);
    }
    printf("\n");
}
void testBasic() {
    printf("\nTest Basic\n");
    Point points[] = {{0, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}, {2, 0}};
    Point hull[10];
    int h = convexHull(points, 6, hull);
    printf("Hull: ");
    printHull(hull, h);
    assert(h == 5);
}
void testNotEnoughPoints() {
    printf("\nTest Not Enough Points\n");
    Point points[] = {{0, 0}, {1, 1}};
    Point hull[10];
    int h = convexHull(points, 2, hull);
    printf("Hull: ");
    printHull(hull, h);
    assert(h == 2);
}
void testSinglePoint() {
    printf("\nTest Single Point\n");
    Point points[] = {{1, 1}};
    Point hull[10];
    int h = convexHull(points, 1, hull);
    printf("Hull: ");
    printHull(hull, h);
    assert(h == 1);
}
void testCollinear() {
    printf("\nTest Collinear\n");
    Point points[] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    Point hull[10];
    int h = convexHull(points, 4, hull);
    printf("Hull: ");
    printHull(hull, h);
    assert(h == 2);
}
void testCollinearWithExtra() {
    printf("\nTest Collinear with Extra\n");
    Point points[] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {0, 3}};
    Point hull[10];
    int h = convexHull(points, 5, hull);
    printf("Hull: ");
    printHull(hull, h);
    assert(h >= 3);
}
void testRandom() {
    printf("\nTest Random Points\n");
    Point points[] = {{0, 0}, {2, 0}, {3, 1}, {3, 3}, {2, 3}, {1, 2}};
    Point hull[10];
    int h = convexHull(points, 6, hull);
    printf("Hull: ");
    printHull(hull, h);
    assert(h == 5);
}
int main() {
    printf("Running Convex Hull Tests\n");
    testBasic();
    testNotEnoughPoints();
    testSinglePoint();
    testCollinear();
    testCollinearWithExtra();
    testRandom();
    printf("\nAll tests passed\n");
    return 0;
}