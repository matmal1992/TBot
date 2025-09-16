#include "../headers/Patterns.h"
#include "gtest/gtest.h"

TEST(CheckTendencyInRow, SingleRiseTrue)
{
    std::deque<double> data = {1.0, 2.0};
    EXPECT_TRUE(CheckTendencyInRow(data, 1, std::greater<>()));
}

TEST(CheckTendencyInRow, SingleRiseFalse)
{
    std::deque<double> data = {2.0, 1.0};
    EXPECT_FALSE(CheckTendencyInRow(data, 1, std::greater<>()));
}

TEST(CheckTendencyInRow, TwoFallsInRowTrue)
{
    std::deque<double> data = {5.0, 4.0, 3.0};
    EXPECT_TRUE(CheckTendencyInRow(data, 2, std::less<>()));
}

TEST(CheckTendencyInRow, TwoFallsInRowFalse)
{
    std::deque<double> data = {5.0, 4.0, 5.0};
    EXPECT_FALSE(CheckTendencyInRow(data, 2, std::less<>()));
}

TEST(PatternsTests, SingleRise)
{
    std::deque<double> data = {1.0, 2.0};
    EXPECT_TRUE(CheckTendencyInRow(data, 1, std::greater<>()));

    data = {2.0, 1.0};
    EXPECT_FALSE(CheckTendencyInRow(data, 1, std::greater<>()));
}

TEST(PatternsTests, TwoRisesInRow)
{
    std::deque<double> data = {1.0, 2.0, 3.0};
    EXPECT_TRUE(CheckTendencyInRow(data, 2, std::greater<>()));

    data = {1.0, 2.0, 1.0};
    EXPECT_FALSE(CheckTendencyInRow(data, 2, std::greater<>()));
}

TEST(PatternsTests, ShortAvgDoubleDecrease)
{
    std::vector<double> short_avg = {5.0, 4.0, 3.0};
    EXPECT_TRUE(ShortAvgDoubleDecrease(short_avg, 0));

    short_avg = {5.0, 5.0, 3.0};
    EXPECT_FALSE(ShortAvgDoubleDecrease(short_avg, 0));
}