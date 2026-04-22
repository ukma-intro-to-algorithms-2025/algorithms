#ifndef POINT_H
#define POINT_H

typedef struct {
    int x, y;
} Point;

double getAngle(Point p0, Point p);
int ccw(Point a, Point b, Point c);

#endif