#ifndef HULL_H
#define HULL_H

#include "point.h"

int convexHull(Point points[], int n, Point hull[]);
void drawPointsAndHull(Point points[], int n, Point hull[], int h);

#endif