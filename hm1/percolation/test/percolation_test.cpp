#include <gtest/gtest.h>
extern "C" {
#include "../src/percolation.h"
}

class PercolationTest : public ::testing::Test {
protected:
    Percolation* p;

    void SetUp() override {
        p = nullptr;
    }

    void TearDown() override {
        if (p) percolation_destroy(p);
    }
};

TEST_F(PercolationTest, Initialization) {
    p = percolation_create(3);
    EXPECT_FALSE(percolation_percolates(p));
    EXPECT_EQ(percolation_number_of_open_sites(p), 0);
}

TEST_F(PercolationTest, OpenCoordinate) {
    p = percolation_create(3);
    percolation_open(p, 1, 1);
    EXPECT_TRUE(percolation_is_open(p, 1, 1));
    EXPECT_EQ(percolation_number_of_open_sites(p), 1);
}

TEST_F(PercolationTest, VerticalPercolation) {
    p = percolation_create(3);
    percolation_open(p, 0, 1);
    percolation_open(p, 1, 1);
    percolation_open(p, 2, 1);
    EXPECT_TRUE(percolation_percolates(p));
}

TEST_F(PercolationTest, HorizontalPercolation) {
    p = percolation_create(1);
    percolation_open(p, 0, 0);
    EXPECT_TRUE(percolation_percolates(p));
}

TEST_F(PercolationTest, NoDiagonalPercolation) {
    p = percolation_create(2);
    percolation_open(p, 0, 0);
    percolation_open(p, 1, 1);
    EXPECT_FALSE(percolation_percolates(p));
}

TEST_F(PercolationTest, ComplexPercolation) {
    p = percolation_create(4);
    percolation_open(p, 0, 1);
    percolation_open(p, 1, 1);
    percolation_open(p, 1, 2);
    percolation_open(p, 2, 2);
    percolation_open(p, 3, 2);
    EXPECT_TRUE(percolation_percolates(p));
}

TEST_F(PercolationTest, OpenCount) {
    p = percolation_create(3);
    percolation_open(p, 0, 0);
    percolation_open(p, 0, 1);
    percolation_open(p, 0, 2);
    EXPECT_EQ(percolation_number_of_open_sites(p), 3);
}