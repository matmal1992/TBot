#include "../headers/Patterns.h"
#include "gtest/gtest.h"

TEST(CheckTendencyInRow, SingleRiseTrue)
{
    std::deque<double> data = {1.0, 2.0};
    EXPECT_TRUE(ConstantTendency(data, 1, std::greater<>()));
}

TEST(CheckTendencyInRow, SingleRiseFalse)
{
    std::deque<double> data = {2.0, 1.0};
    EXPECT_FALSE(ConstantTendency(data, 1, std::greater<>()));
}

TEST(CheckTendencyInRow, TwoFallsInRowTrue)
{
    std::deque<double> data = {5.0, 4.0, 3.0};
    EXPECT_TRUE(ConstantTendency(data, 2, std::less<>()));
}

TEST(CheckTendencyInRow, TwoFallsInRowFalse)
{
    std::deque<double> data = {5.0, 4.0, 5.0};
    EXPECT_FALSE(ConstantTendency(data, 2, std::less<>()));
}

TEST(PatternsTests, SingleRise)
{
    std::deque<double> data = {1.0, 2.0};
    EXPECT_TRUE(ConstantTendency(data, 1, std::greater<>()));

    data = {2.0, 1.0};
    EXPECT_FALSE(ConstantTendency(data, 1, std::greater<>()));
}

TEST(PatternsTests, TwoRisesInRow)
{
    std::deque<double> data = {1.0, 2.0, 3.0};
    EXPECT_TRUE(ConstantTendency(data, 2, std::greater<>()));

    data = {1.0, 2.0, 1.0};
    EXPECT_FALSE(ConstantTendency(data, 2, std::greater<>()));
}

TEST(PatternsTests, ShortAvgDoubleDecrease)
{
    std::vector<double> short_avg = {5.0, 4.0, 3.0};
    EXPECT_TRUE(ConstantTendency(short_avg, 0, std::less<>()));

    short_avg = {5.0, 5.0, 3.0};
    EXPECT_FALSE(ConstantTendency(short_avg, 0, std::less<>()));
}