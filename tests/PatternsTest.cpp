#include "../headers/Patterns.h"
#include "gtest/gtest.h"

TEST(ConstantTendencyTest, SingleRiseTrueForDequeAndVector)
{
    std::deque<double> d_data = {1.0, 2.0};
    EXPECT_TRUE(ConstantTendency(d_data, 1, std::greater<>()));

    d_data = {2.0, 1.0};
    EXPECT_FALSE(ConstantTendency(d_data, 1, std::greater<>()));

    std::vector<double> v_data = {1.9999, 2.0};
    EXPECT_TRUE(ConstantTendency(v_data, 1, std::greater<>()));
}

TEST(ConstantTendencyTest, SingleFallTrueForDequeAndVector)
{
    std::deque<double> d_data = {2.0, 1.0};
    EXPECT_TRUE(ConstantTendency(d_data, 1, std::less<>()));

    d_data = {1.0, 2.0};
    EXPECT_FALSE(ConstantTendency(d_data, 1, std::less<>()));

    std::vector<double> v_data = {2.0, 1.9999};
    EXPECT_TRUE(ConstantTendency(v_data, 1, std::less<>()));
}

TEST(ConstantTendencyTest, DoubleRiseTrue)
{
    std::deque<double> d_data = {1.0, 2.0, 3.0};
    EXPECT_TRUE(ConstantTendency(d_data, 2, std::greater<>()));

    d_data = {1.0, 3.0, 2.0};
    EXPECT_FALSE(ConstantTendency(d_data, 2, std::greater<>()));
}

TEST(ConstantTendencyTest, DoubleFallTrue)
{
    std::deque<double> d_data = {3.0, 2.0, 1.0};
    EXPECT_TRUE(ConstantTendency(d_data, 2, std::less<>()));

    d_data = {3.0, 1.0, 2.0};
    EXPECT_FALSE(ConstantTendency(d_data, 2, std::less<>()));
}

TEST(ConstantTendencyTest, FiveTimesInRowFallTrue)
{
    std::deque<double> d_data = {10.0, 8.0, 6.0, 4.0, 2.0, 0.0};
    EXPECT_TRUE(ConstantTendency(d_data, 5, std::less<>()));

    d_data = {10.0, 8.0, 6.0, 4.0, 2.0, 1.0}; // still strictly decreasing
    EXPECT_TRUE(ConstantTendency(d_data, 5, std::less<>()));

    d_data = {10.0, 8.0, 6.0, 4.0, 2.0, 3.0}; // last value breaks the fall
    EXPECT_FALSE(ConstantTendency(d_data, 5, std::less<>()));

    d_data = {10.0, 11.0, 6.0, 4.0, 2.0, 3.0}; // second value breaks the fall
    EXPECT_FALSE(ConstantTendency(d_data, 5, std::less<>()));
}

TEST(ConstantTendencyTest, FiveTimesInRowRiseTrue)
{
    std::deque<double> d_data = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0};
    EXPECT_TRUE(ConstantTendency(d_data, 5, std::greater<>()));

    d_data = {0.0, 2.0, 4.0, 6.0, 8.0, 9.0}; // still strictly increasing
    EXPECT_TRUE(ConstantTendency(d_data, 5, std::greater<>()));

    d_data = {0.0, 2.0, 4.0, 6.0, 8.0, 7.0}; // last value breaks the rise
    EXPECT_FALSE(ConstantTendency(d_data, 5, std::greater<>()));

    d_data = {1.0, 0.5, 4.0, 6.0, 8.0, 7.0}; // second value breaks the rise
    EXPECT_FALSE(ConstantTendency(d_data, 5, std::greater<>()));
}

TEST(ConstantTendencyTest, EqualValuesInRow)
{
    std::deque<double> d_data = {1.0, 1.0, 3.0};
    EXPECT_FALSE(ConstantTendency(d_data, 2, std::greater<>()));

    d_data = {1.0, 1.0, 0.5};
    EXPECT_FALSE(ConstantTendency(d_data, 2, std::less<>()));
}

TEST(ConstantTendencyTest, SingleValueInContainer)
{
    std::deque<double> d_data = {1.0};
    EXPECT_FALSE(ConstantTendency(d_data, 1, std::greater<>()));
    EXPECT_FALSE(ConstantTendency(d_data, 1, std::less<>()));
}

TEST(ConstantTendencyTest, EmptyContainer)
{
    std::deque<double> d_data = {};
    EXPECT_FALSE(ConstantTendency(d_data, 1, std::greater<>()));
    EXPECT_FALSE(ConstantTendency(d_data, 1, std::less<>()));
}
