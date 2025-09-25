#include "../headers/BotSimulator.h"
#include "gtest/gtest.h"

TEST(BotSimulatorTest, NoPricesMeansNoActions)
{
    std::vector<double> prices = {};
    BotSimulator bot(prices, 2, 4);

    bot.RunSimulator();
    const auto& data = bot.GetSimulatedData();

    EXPECT_TRUE(data.actions.empty());
    EXPECT_EQ(data.opens, 0u);
    EXPECT_EQ(data.closes, 0u);
    EXPECT_DOUBLE_EQ(data.balance, 0.0);
}

TEST(BotSimulatorTest, AlwaysRisingPricesOpensOnceAndClosesNever)
{
    std::vector<double> prices = {1.0, 2.0, 3.0, 4.0};
    BotSimulator bot(prices, 2, 4);

    bot.RunSimulator();
    const auto& data = bot.GetSimulatedData();

    EXPECT_EQ(data.opens, 1u);
    EXPECT_EQ(data.closes, 0u);
    EXPECT_TRUE(std::any_of(data.actions.begin(), data.actions.end(), [](action a) { return a == action::open; }));
}

TEST(BotSimulatorTest, RisingThenFallingClosesPosition)
{
    std::vector<double> prices = {1.0, 2.0, 3.0, 2.0, 1.5};
    BotSimulator bot(prices, 2, 4);

    bot.RunSimulator();
    const auto& data = bot.GetSimulatedData();

    EXPECT_EQ(data.opens, 1u);
    EXPECT_EQ(data.closes, 1u);
    EXPECT_DOUBLE_EQ(data.balance, prices.back() - prices[2]);
}

TEST(BotSimulatorTest, FlatPricesShouldNotTriggerOpenOrClose)
{
    std::vector<double> prices(10, 5.0);
    BotSimulator bot(prices, 2, 4);

    bot.RunSimulator();
    const auto& data = bot.GetSimulatedData();

    EXPECT_EQ(data.opens, 0u);
    EXPECT_EQ(data.closes, 0u);
    EXPECT_TRUE(std::all_of(data.actions.begin(), data.actions.end(), [](action a) { return a == action::none; }));
}

TEST(BotSimulatorTest, CalculateAverageWorksForShorterThanPeriod)
{
    std::vector<double> prices = {10.0, 20.0};
    BotSimulator bot(prices, 5, 10);

    bot.RunSimulator();
    const auto& data = bot.GetSimulatedData();

    ASSERT_EQ(data.short_averages.size(), prices.size());
    EXPECT_DOUBLE_EQ(data.short_averages[0], 10.0);
    EXPECT_DOUBLE_EQ(data.short_averages[1], 15.0);
}