#include <gtest/gtest.h>

extern "C" {
#include "randomized_queue.h"
}

TEST(RandomizedQueueTest, EmptyQueue) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    EXPECT_TRUE(RandomizedQueueEmpty(rq));
    EXPECT_EQ(RandomizedQueueSize(rq), 0);
    RandomizedQueueDestroy(rq);
}
TEST(RandomizedQueueTest, EnqueueDequeueSize) {
    RandomizedQueuePtr rq = RandomizedQueueInit();
    int a = 1, b = 2, c = 3;
    RandomizedQueueEnqueue(rq, &a);
    RandomizedQueueEnqueue(rq, &b);
    RandomizedQueueEnqueue(rq, &c);
    EXPECT_EQ(RandomizedQueueSize(rq), 3);
    int* x = (int*)RandomizedQueueDequeue(rq);
    EXPECT_TRUE(*x == 1 || *x == 2 || *x == 3);
    EXPECT_EQ(RandomizedQueueSize(rq), 2);
    RandomizedQueueDestroy(rq);
}
TEST(RandomizedQueueTest, WorksWithStructs) {
    struct Point {
        int x, y;
    };
    RandomizedQueuePtr rq = RandomizedQueueInit();
    Point p1{1, 2};
    Point p2{3, 4};
    RandomizedQueueEnqueue(rq, &p1);
    RandomizedQueueEnqueue(rq, &p2);
    Point* p = (Point*)RandomizedQueueDequeue(rq);
    EXPECT_TRUE(
        (p->x == 1 && p->y == 2) ||
        (p->x == 3 && p->y == 4)
    );
    RandomizedQueueDestroy(rq);
}
