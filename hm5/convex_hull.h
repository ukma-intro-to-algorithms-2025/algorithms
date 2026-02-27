#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

typedef struct {
    int x, y;
} Point;

double getAngle(Point p0, Point p);
int ccw(Point a, Point b, Point c);
int compare_points(const void* p1, const void* p2);
int compare_by_polar_angle(const void* p1, const void* p2, void* p0_ptr);
void quick_sort_points(Point arr[], int low, int high);
void merge_sort_points(Point arr[], int l, int r, Point p0);
int convexHull(Point points[], int n, Point hull[]);
void drawPointsAndHull(Point points[], int n, Point hull[], int h);

#endif