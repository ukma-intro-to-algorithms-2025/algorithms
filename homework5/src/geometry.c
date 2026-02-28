#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/point.h"

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