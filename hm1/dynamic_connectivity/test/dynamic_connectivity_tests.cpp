#include <gtest/gtest.h>

extern "C" {
#include "../src/dynamic_connectivity.h"
}

class DynamicConnectivityTest : public ::testing::Test {
protected:
    DynamicConnectivity* dc;

    void SetUp() override {
        dc = dc_create(10);
    }

    void TearDown() override {
        dc_free(dc);
    }
};

TEST_F(DynamicConnectivityTest, Initialization) {
    ASSERT_NE(dc, nullptr);
}

TEST_F(DynamicConnectivityTest, InitializationCapacity) {
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(dc_root(dc, i), i);
    }
}

TEST_F(DynamicConnectivityTest, RootFunction) {
    dc_union(dc, 1, 2);
    dc_union(dc, 2, 3);

    EXPECT_EQ(dc_root(dc, 1), dc_root(dc, 3));
}

TEST_F(DynamicConnectivityTest, ConnectedFunction) {
    dc_union(dc, 4, 5);

    EXPECT_TRUE(dc_connected(dc, 4, 5));
    EXPECT_FALSE(dc_connected(dc, 4, 6));
}

TEST_F(DynamicConnectivityTest, UnionFunction) {
    dc_union(dc, 1, 2);
    dc_union(dc, 2, 3);

    EXPECT_TRUE(dc_connected(dc, 1, 3));
}

TEST_F(DynamicConnectivityTest, TestTwoConnectedComponents) {
    dc_union(dc, 0, 1);
    dc_union(dc, 1, 2);

    dc_union(dc, 3, 4);
    dc_union(dc, 4, 5);

    EXPECT_TRUE(dc_connected(dc, 0, 2));
    EXPECT_TRUE(dc_connected(dc, 3, 5));
    EXPECT_FALSE(dc_connected(dc, 0, 5));
}

TEST_F(DynamicConnectivityTest, TestWeightedUnion) {
    dc_union(dc, 1, 2);
    dc_union(dc, 2, 3);
    dc_union(dc, 4, 5);
    dc_union(dc, 3, 5);

    EXPECT_TRUE(dc_connected(dc, 1, 4));
}

TEST_F(DynamicConnectivityTest, TestPathCompression) {
    dc_union(dc, 1, 2);
    dc_union(dc, 2, 3);
    dc_union(dc, 3, 4);

    int root_before = dc_root(dc, 4);
    int root_after  = dc_root(dc, 1);

    EXPECT_EQ(root_before, root_after);
}
