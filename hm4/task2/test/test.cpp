#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <gtest/gtest.h>
#include "../include/point.h"

class PointTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PointTest, CreateAndDestroyPoint) {
    PointPtr p = create_point(5, 10);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->x, 5);
    EXPECT_EQ(p->y, 10);
    destroy_point(p);
}

TEST_F(PointTest, ComparePoints) {
    Point p1 = {1, 2};
    Point p2 = {2, 2};
    Point p3 = {1, 3};
    Point p4 = {1, 2};
    
    EXPECT_LT(compare_points(&p1, &p2), 0);
    EXPECT_GT(compare_points(&p2, &p1), 0);
    EXPECT_LT(compare_points(&p1, &p3), 0);
    EXPECT_GT(compare_points(&p3, &p1), 0);
    EXPECT_EQ(compare_points(&p1, &p4), 0);
}

TEST_F(PointTest, SlopeCalculation) {
    PointPtr p1 = create_point(0, 0);
    PointPtr p2 = create_point(1, 1);
    PointPtr p3 = create_point(2, 2);
    PointPtr p4 = create_point(0, 1);
    PointPtr p5 = create_point(1, 0);
    
    EXPECT_DOUBLE_EQ(slope_to(p1, p2), 1.0);
    EXPECT_DOUBLE_EQ(slope_to(p1, p3), 1.0);
    EXPECT_DOUBLE_EQ(slope_to(p2, p3), 1.0);
    EXPECT_DOUBLE_EQ(slope_to(p1, p4), INFINITY);
    EXPECT_DOUBLE_EQ(slope_to(p1, p5), 0.0);
    EXPECT_DOUBLE_EQ(slope_to(p1, p1), -INFINITY);
    
    destroy_point(p1);
    destroy_point(p2);
    destroy_point(p3);
    destroy_point(p4);
    destroy_point(p5);
}

TEST_F(PointTest, FileIO) {
    FILE* f = fopen("test_input.txt", "w");
    ASSERT_NE(f, nullptr);
    fprintf(f, "5\n0 0\n1 1\n2 2\n3 3\n4 4\n");
    fclose(f);
    
    int n;
    PointPtr* points = read_points_from_file("test_input.txt", &n);
    
    ASSERT_NE(points, nullptr);
    EXPECT_EQ(n, 5);
    EXPECT_EQ(points[0]->x, 0);
    EXPECT_EQ(points[0]->y, 0);
    EXPECT_EQ(points[4]->x, 4);
    EXPECT_EQ(points[4]->y, 4);
    
    free_points_array(points, n);
    remove("test_input.txt");
}

TEST_F(PointTest, SortingAlgorithms) {
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    int arr1[9];
    memcpy(arr1, arr, sizeof(arr));
    insertion_sort(arr1, n, sizeof(int), 
                   [](const void* a, const void* b) -> int {
                       return *(int*)a - *(int*)b;
                   });
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr1[i], sorted[i]);
    }
    
    int arr2[9];
    memcpy(arr2, arr, sizeof(arr));
    selection_sort(arr2, n, sizeof(int), 
                   [](const void* a, const void* b) -> int {
                       return *(int*)a - *(int*)b;
                   });
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr2[i], sorted[i]);
    }
    
    int arr3[9];
    memcpy(arr3, arr, sizeof(arr));
    shell_sort(arr3, n, sizeof(int), 
               [](const void* a, const void* b) -> int {
                   return *(int*)a - *(int*)b;
               });
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(arr3[i], sorted[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}