#include <gtest/gtest.h>

#define N 10

int sz[N]; 
bool connected__quick_find(const int* id, int p, int q) { //чи елементи p і q належать одній компоненті
    return id[p] == id[q];
}

void union__quick_find(int* id, int p, int q) { //обʼєднує компоненти, в яких знаходяться p і q 
    int pid = id[p];
    int qid = id[q];
    for (int i = 0; i < N; ++i) {
        if (id[i] == pid) {
            id[i] = qid;
        }
    }
}

int root__quick_union(const int* id, int i) {
    while (i != id[i]) {
        i = id[i];
    }
    return i;
}

bool connected__quick_union(const int* id, int p, int q) { //чи p і q в одній компоненті
    return root__quick_union(id, p) == root__quick_union(id, q);
}

void union__quick_union(int* id, int p, int q) { //обʼєднує компоненти p і q 
    int i = root__quick_union(id, p); 
    int j = root__quick_union(id, q);
    id[i] = j;
}

void union__weighted_quick_union(int* id, int p, int q) { //обʼєднання з урахуванням розміру дерев 
    int i = root__quick_union(id, p);
    int j = root__quick_union(id, q);

    if (i == j) return;

    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    } else {
        id[j] = i;
        sz[i] += sz[j];
    }
}

int root__quick_union_path_compression(int* id, int i) {
    while (i != id[i]) {
        id[i] = id[id[i]];  
        i = id[i];
    }
    return i;
}

class QuickUnionTest : public ::testing::Test {
protected:
    int id[N];

    void SetUp() override {
        for (int i = 0; i < N; ++i) {
            id[i] = i;
            sz[i] = 1;
        }
    }
};

TEST_F(QuickUnionTest, Connected__QuickFind) {
    id[3] = id[4] = 1;
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    EXPECT_FALSE(connected__quick_find(id, 3, 5));
}

TEST_F(QuickUnionTest, Union__QuickFind) {
    union__quick_find(id, 3, 4);
    EXPECT_TRUE(connected__quick_find(id, 3, 4));
    EXPECT_FALSE(connected__quick_find(id, 3, 5));
}

TEST_F(QuickUnionTest, Root__QuickUnion) {
    id[1] = 0;
    id[2] = 1;
    id[3] = 2;
    EXPECT_EQ(root__quick_union(id, 3), 0);
}

TEST_F(QuickUnionTest, Connected__QuickUnion) {
    union__quick_union(id, 3, 4);
    EXPECT_TRUE(connected__quick_union(id, 3, 4));
    EXPECT_FALSE(connected__quick_union(id, 3, 5));
}

TEST_F(QuickUnionTest, Union__QuickUnion) {
    union__quick_union(id, 1, 2);
    union__quick_union(id, 2, 3);
    EXPECT_TRUE(connected__quick_union(id, 1, 3));
}

TEST_F(QuickUnionTest, Union__WeightedQuickUnion) {
    union__weighted_quick_union(id, 1, 2);
    union__weighted_quick_union(id, 3, 4);
    union__weighted_quick_union(id, 1, 4);
    EXPECT_TRUE(connected__quick_union(id, 2, 3));
}

TEST_F(QuickUnionTest, Root__QuickUnionPathCompression) {
    id[1] = 0;
    id[2] = 1;
    id[3] = 2;

    int r = root__quick_union_path_compression(id, 3);
    EXPECT_EQ(r, 0);
    EXPECT_EQ(id[3], 1); 
}
