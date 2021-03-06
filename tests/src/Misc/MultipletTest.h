/* This file is part of PyMesh. Copyright (c) 2015 by Qingnan Zhou */
#pragma once
#include <string>

#include <Misc/Multiplet.h>

TEST(MultipletTest, Equality) {
    Quadruplet t1(1, 2, 3, 4);
    Quadruplet t2(3, 2, 1, 4);
    ASSERT_EQ(t1, t2);
}

TEST(MultipletTest, Equality2) {
    Quadruplet t1(1, 1, 1);
    Quadruplet t2(1, 1, 1);
    ASSERT_EQ(t1, t2);
}

TEST(MultipletTest, LessThan) {
    Quadruplet t1(1, 2, 3, 1);
    Quadruplet t2(4, 0, 0, 0);
    ASSERT_LT(t1, t2);
}

TEST(MultipletTest, LessThan2) {
    Quadruplet t1(1, 2, 3, 0);
    Quadruplet t2(3, 0, 0, 0);
    ASSERT_LT(t2, t1);
}

TEST(MultipletTest, DataRecovery) {
    Quadruplet t1(1, 2, 3 ,4);
    VectorI data = t1.get_ori_data();
    ASSERT_EQ(1, data[0]);
    ASSERT_EQ(2, data[1]);
    ASSERT_EQ(3, data[2]);
    ASSERT_EQ(4, data[3]);
}

TEST(MultipletTest, DataRecovery2) {
    Triplet t1(5, 4, 3);
    VectorI data = t1.get_data();
    Triplet t2(data[0], data[1], data[2]);
    ASSERT_EQ(t1, t2);
}
