#include <gtest/gtest.h>
#include "pythagorean_triangle.h"

TEST(PythagoreanTriangleInt, ThreeFourFive)
{
    PythagoreanTriangle<int> t(3, 4);
    EXPECT_DOUBLE_EQ(t.get_hypotenuse(), 5.0);
    EXPECT_DOUBLE_EQ(t.get_area(), 6.0);
    EXPECT_TRUE(t.is_valid());
}

TEST(PythagoreanTriangleDouble, FiveTwelveThirteen)
{
    PythagoreanTriangle<double> t(5.0, 12.0);
    EXPECT_DOUBLE_EQ(t.get_hypotenuse(), 13.0);
    EXPECT_DOUBLE_EQ(t.get_area(), 30.0);
    EXPECT_TRUE(t.is_valid());
}

TEST(PythagoreanTriangleFloat, SixEightTen)
{
    PythagoreanTriangle<float> t(6.0f, 8.0f);
    EXPECT_NEAR(t.get_hypotenuse(), 10.0, 1e-6);
    EXPECT_NEAR(t.get_area(), 24.0, 1e-6);
    EXPECT_TRUE(t.is_valid());
}

#if 0
TEST(PythagoreanTriangleEdge, ZeroZero)
{
    PythagoreanTriangle<int> t(0, 0);
    EXPECT_DOUBLE_EQ(t.get_hypotenuse(), 0.0);
    EXPECT_DOUBLE_EQ(t.get_area(), 0.0);
    EXPECT_TRUE(t.is_valid());
}
#endif

TEST(PythagoreanTriangleEdge, ZeroZero)
{
    PythagoreanTriangle<int> t(0, 0);
    EXPECT_DOUBLE_EQ(t.get_hypotenuse(), 0.0);
    EXPECT_DOUBLE_EQ(t.get_area(), 0.0);
    EXPECT_FALSE(t.is_valid());   // changed
}

TEST(PythagoreanTriangleInvalid, NegativeSide)
{
    PythagoreanTriangle<int> t(-3, 4);
    EXPECT_FALSE(t.is_valid());
}

