#include "../headers/Patterns.h"
#include "gtest/gtest.h"

namespace patterns
{
TEST(ConstantTendencyTest, SingleRiseTrueForDequeAndVector)
{
    std::deque<double> d_data = {1.0, 2.0};
    EXPECT_TRUE(ConstantTendency(d_data, 2, std::greater<>()));

    d_data = {2.0, 1.0};
    EXPECT_FALSE(ConstantTendency(d_data, 2, std::greater<>()));

    std::vector<double> v_data = {1.9999, 2.0};
    EXPECT_TRUE(ConstantTendency(v_data, 2, std::greater<>()));
}

TEST(ConstantTendencyTest, SingleFallTrueForDequeAndVector)
{
    std::deque<double> d_data = {2.0, 1.0};
    EXPECT_TRUE(ConstantTendency(d_data, 2, std::less<>()));

    d_data = {1.0, 2.0};
    EXPECT_FALSE(ConstantTendency(d_data, 2, std::less<>()));

    std::vector<double> v_data = {2.0, 1.9999};
    EXPECT_TRUE(ConstantTendency(v_data, 2, std::less<>()));
}

TEST(ConstantTendencyTest, DoubleRiseTrue)
{
    std::deque<double> d_data = {1.0, 2.0, 3.0};
    EXPECT_TRUE(ConstantTendency(d_data, 3, std::greater<>()));

    d_data = {1.0, 3.0, 2.0};
    EXPECT_FALSE(ConstantTendency(d_data, 3, std::greater<>()));
}

TEST(ConstantTendencyTest, DoubleFallTrue)
{
    std::deque<double> d_data = {3.0, 2.0, 1.0};
    EXPECT_TRUE(ConstantTendency(d_data, 3, std::less<>()));

    d_data = {3.0, 1.0, 2.0};
    EXPECT_FALSE(ConstantTendency(d_data, 3, std::less<>()));
}

TEST(ConstantTendencyTest, FiveTimesInRowFallTrue)
{
    std::deque<double> d_data = {10.0, 8.0, 6.0, 4.0, 2.0, 0.0};
    EXPECT_TRUE(ConstantTendency(d_data, 6, std::less<>()));

    d_data = {10.0, 8.0, 6.0, 4.0, 2.0, 3.0}; // last value breaks the fall
    EXPECT_FALSE(ConstantTendency(d_data, 6, std::less<>()));

    d_data = {10.0, 11.0, 6.0, 4.0, 2.0, 3.0}; // second value breaks the fall
    EXPECT_FALSE(ConstantTendency(d_data, 6, std::less<>()));
}

TEST(ConstantTendencyTest, FiveTimesInRowRiseTrue)
{
    std::deque<double> d_data = {0.0, 2.0, 4.0, 6.0, 8.0, 10.0};
    EXPECT_TRUE(ConstantTendency(d_data, 6, std::greater<>()));

    d_data = {0.0, 2.0, 4.0, 6.0, 8.0, 9.0}; // still strictly increasing
    EXPECT_TRUE(ConstantTendency(d_data, 6, std::greater<>()));

    d_data = {0.0, 2.0, 4.0, 6.0, 8.0, 7.0}; // last value breaks the rise
    EXPECT_FALSE(ConstantTendency(d_data, 6, std::greater<>()));

    d_data = {1.0, 0.5, 4.0, 6.0, 8.0, 7.0}; // second value breaks the rise
    EXPECT_FALSE(ConstantTendency(d_data, 6, std::greater<>()));
}

TEST(ConstantTendencyTest, EqualValuesInRow)
{
    std::deque<double> d_data = {1.0, 2.0, 2.0};
    EXPECT_FALSE(ConstantTendency(d_data, 2, std::greater<>()));

    d_data = {1.0, 0.5, 0.5};
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

TEST(ConstantTendencyTest, CheckIfFunctionWorksForIndexInTheMiddleOfContainer)
{
    std::deque<double> d_data = {0.0, 2.0, 1.0, 4.0, 2.0, 3.0};
    EXPECT_TRUE(ConstantTendency(d_data, 2, std::greater<>())); // checks only last two values: 2.0, 3.0
    EXPECT_FALSE(ConstantTendency(d_data, 3, std::greater<>())); // checks last three values: 4.0, 2.0, 3.0
}

TEST(ConstantTendencyTest, CheckNEqualsOne)
{
    std::deque<double> d_data = {0.0, 2.0, 1.0, 4.0, 2.0, 3.0};
    EXPECT_FALSE(ConstantTendency(d_data, 1, std::greater<>()));
}

TEST(IsSuddenChangeTest, DetectsSuddenRise)
{
    std::deque<double> data = {100.0, 200.0};
    EXPECT_TRUE(IsSuddenChange(data, change_direction::rise));

    data = {100.0, 150.0};
    EXPECT_FALSE(IsSuddenChange(data, change_direction::rise));
}

TEST(IsSuddenChangeTest, DetectsSuddenFall)
{
    std::deque<double> data = {100.0, 30.0};
    EXPECT_TRUE(IsSuddenChange(data, change_direction::fall));

    data = {100.0, 50.0};
    EXPECT_FALSE(IsSuddenChange(data, change_direction::fall));
}

TEST(IsSuddenChangeTest, NotEnoughData)
{
    std::deque<double> empty_data {};
    EXPECT_FALSE(IsSuddenChange(empty_data, change_direction::rise));
    EXPECT_FALSE(IsSuddenChange(empty_data, change_direction::fall));

    std::deque<double> single_data = {100.0};
    EXPECT_FALSE(IsSuddenChange(single_data, change_direction::rise));
    EXPECT_FALSE(IsSuddenChange(single_data, change_direction::fall));
}

TEST(IsSuddenChangeTest, BorderlineCases)
{
    std::deque<double> data = {100.0, 190.0};
    EXPECT_FALSE(IsSuddenChange(data, change_direction::rise));

    data = {100.0, 40.0};
    EXPECT_FALSE(IsSuddenChange(data, change_direction::fall));
}

TEST(IsSuddenChangeTest, BiggerDataContainer)
{
    std::deque<double> data = {0.0, 2.0, 1.0, 4.0, 2.0, 3.0, 100.0, 191.0};
    EXPECT_TRUE(IsSuddenChange(data, change_direction::rise));

    data = {0.0, 2.0, 1.0, 4.0, 2.0, 3.0, 100.0, 30.0};
    EXPECT_TRUE(IsSuddenChange(data, change_direction::fall));
}

TEST(SamePricesInRowTest, AllSame)
{
    std::deque<double> d = {5.0, 5.0, 5.0, 5.0};
    EXPECT_TRUE(SamePricesInRow(d, 4));
}

TEST(SamePricesInRowTest, LastTwoSameButNotThree)
{
    std::deque<double> d = {1.0, 2.0, 3.0, 3.0};
    EXPECT_TRUE(SamePricesInRow(d, 2));
    EXPECT_FALSE(SamePricesInRow(d, 3));
}

TEST(SamePricesInRowTest, NotEnoughElements)
{
    std::deque<double> d = {1.0};
    EXPECT_FALSE(SamePricesInRow(d, 2));
}

} // namespace patterns