#include <gtest/gtest.h>

extern "C" {
#include "deque.h"
}
TEST(DequeTest, EmptyDeque) {
    DequePtr d = DequeInit();
    EXPECT_TRUE(DequeEmpty(d));
    EXPECT_EQ(DequeSize(d), 0);
    DequeDestroy(d);
}
TEST(DequeTest, AddFirstRemoveFirst) {
    DequePtr d = DequeInit();
    int a = 10;
    int b = 20;
    DequeAddFirst(d, &a);
    DequeAddFirst(d, &b);
    EXPECT_EQ(*(int*)DequeRemoveFirst(d), 20);
    EXPECT_EQ(*(int*)DequeRemoveFirst(d), 10);
    EXPECT_TRUE(DequeEmpty(d));
    DequeDestroy(d);
}
TEST(DequeTest, AddLastRemoveLast) {
    DequePtr d = DequeInit();
    int a = 1;
    int b = 2;
    DequeAddLast(d, &a);
    DequeAddLast(d, &b);
    EXPECT_EQ(*(int*)DequeRemoveLast(d), 2);
    EXPECT_EQ(*(int*)DequeRemoveLast(d), 1);
    DequeDestroy(d);
}
TEST(DequeTest, MixedOperations) {
    DequePtr d = DequeInit();
    int a = 1, b = 2, c = 3;
    DequeAddFirst(d, &a);
    DequeAddLast(d, &b);
    DequeAddFirst(d, &c);
    EXPECT_EQ(*(int*)DequeRemoveLast(d), 2);
    EXPECT_EQ(*(int*)DequeRemoveFirst(d), 3);
    EXPECT_EQ(*(int*)DequeRemoveFirst(d), 1);
    DequeDestroy(d);
}
struct Point {
    int x, y;
};
TEST(DequeTest, WorksWithStructs) {
    DequePtr d = DequeInit();
    Point p1{1, 2};
    Point p2{3, 4};
    DequeAddLast(d, &p1);
    DequeAddLast(d, &p2);
    Point* r = (Point*)DequeRemoveFirst(d);
    EXPECT_EQ(r->x, 1);
    EXPECT_EQ(r->y, 2);
    DequeDestroy(d);
}
