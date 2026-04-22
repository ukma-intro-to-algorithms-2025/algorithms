#include "../include/point.h"
#include <math.h>

double getAngle(Point p0, Point p) {
    int dx = p.x - p0.x;
    int dy = p.y - p0.y;
    
    if (dx == 0 && dy == 0) return -1.0;  
    
    return atan2(dy, dx);
}

int ccw(Point a, Point b, Point c) {
    int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    
    if (area > 0) return 1;
    if (area < 0) return -1;
    return 0;
}