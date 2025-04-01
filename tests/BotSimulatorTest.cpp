#include <gtest/gtest.h>
#include "../headers/BotSimulator.h"

class BotSimulatorTest : public ::testing::Test
{
protected:
    BotSimulator bot;

    void SetUp() override
    {
        bot.prices_ = {100, 90, 80, 70, 60, 50, 40}; // Example price data
        bot.percentage_peak_profit = 1.2;            // Example threshold (20% increase)
    }
};

// 🔹 Test AddRecord()
TEST_F(BotSimulatorTest, AddRecord_AddsElementsCorrectly)
{
    bot.AddRecord(0);
    bot.AddRecord(1);
    bot.AddRecord(2);
    bot.AddRecord(3);
    bot.AddRecord(4);

    ASSERT_EQ(bot.current_records.size(), 5);
    EXPECT_EQ(bot.current_records.front(), bot.prices_[0]);
    EXPECT_EQ(bot.current_records.back(), bot.prices_[4]);

    bot.AddRecord(5); // Should remove first and add new one
    ASSERT_EQ(bot.current_records.size(), 5);
    EXPECT_EQ(bot.current_records.back(), bot.prices_[5]);
}

// 🔹 Test IsConstantFall()
TEST_F(BotSimulatorTest, IsConstantFall_TrueWhenDecreasing)
{
    bot.AddRecord(0);
    bot.AddRecord(1);
    bot.AddRecord(2);
    bot.AddRecord(3);

    EXPECT_TRUE(bot.IsConstantFall()); // Always decreasing
}

TEST_F(BotSimulatorTest, IsConstantFall_FalseWhenNotDecreasing)
{
    bot.AddRecord(1);
    bot.AddRecord(0); // Increase
    bot.AddRecord(2);

    EXPECT_FALSE(bot.IsConstantFall());
}

// 🔹 Test IsConstantRise()
TEST_F(BotSimulatorTest, IsConstantRise_TrueWhenIncreasing)
{
    bot.AddRecord(4);
    bot.AddRecord(3);
    bot.AddRecord(2);
    bot.AddRecord(1);

    EXPECT_TRUE(bot.IsConstantRise());
}

TEST_F(BotSimulatorTest, IsConstantRise_FalseWhenNotIncreasing)
{
    bot.AddRecord(3);
    bot.AddRecord(2);
    bot.AddRecord(4); // Breaks pattern

    EXPECT_FALSE(bot.IsConstantRise());
}

// 🔹 Test IsSuddenRise()
TEST_F(BotSimulatorTest, IsSuddenRise_DetectsRise)
{
    bot.AddRecord(0); // 100
    bot.AddRecord(1); // 90
    bot.AddRecord(5); // 50 (no sudden rise yet)
    bot.AddRecord(2); // 80
    bot.AddRecord(6); // 40 (Sudden rise: 40 → 80 is 100% increase)

    EXPECT_TRUE(bot.IsSuddenRise());
}

TEST_F(BotSimulatorTest, IsSuddenRise_FalseWhenNoJump)
{
    bot.AddRecord(3);
    bot.AddRecord(2);
    bot.AddRecord(1);

    EXPECT_FALSE(bot.IsSuddenRise());
}

// 🔹 Test IsSuddenFall()
TEST_F(BotSimulatorTest, IsSuddenFall_DetectsFall)
{
    bot.AddRecord(0); // 100
    bot.AddRecord(1); // 90
    bot.AddRecord(2); // 80
    bot.AddRecord(3); // 70
    bot.AddRecord(6); // 40 (Sudden fall: 70 → 40 is more than 20% drop)

    EXPECT_TRUE(bot.IsSuddenFall());
}

TEST_F(BotSimulatorTest, IsSuddenFall_FalseWhenNoDrop)
{
    bot.AddRecord(0);
    bot.AddRecord(1);
    bot.AddRecord(2);

    EXPECT_FALSE(bot.IsSuddenFall());
}
