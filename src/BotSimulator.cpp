#include "..\headers\BotSimulator.h"

BotSimulator::BotSimulator(const std::vector<double>& prices, const int short_period, const int long_period)
    : prices_(prices)
    , short_period_(short_period)
    , long_period_(long_period)
{
}

void BotSimulator::AddRecord(int record_index)
{
    if (current_records_.size() >= long_period_)
    {
        current_records_.pop_front();
    }

    current_records_.push_back(prices_.at(record_index));
    data_.short_averages.push_back(CalculateAverage(short_period_));
    data_.long_averages.push_back(CalculateAverage(long_period_));
}

void BotSimulator::RunSimulator()
{
    for (size_t i {0}; i < prices_.size(); ++i)
    {
        AddRecord(i);
        MakeDecision();
    }
}

void BotSimulator::OpenPosition()
{
    data_.actions.push_back(action::open);
    position_opened = true;
    data_.opens++;
    open_value = current_records_.back();
}

void BotSimulator::ClosePosition()
{
    data_.actions.push_back(action::close);
    position_opened = false;
    data_.closes++;
    data_.balance += current_records_.back() - open_value - spread_;
}

void BotSimulator::MakeDecision()
{
    // bool single_rise = SingleRise(current_records);
    // bool single_fall = SingleFall(current_records);
    // bool increase_in_row = IncreasesInRow(data_.short_averages, 2);
    // bool decrease_in_row = DecreasesInRow(data_.short_averages, 2);
    // bool two_same_prices = TwoSamePriceInRow(current_records);
    // bool short_avg_greater = CalculateAverage(short_period_) > CalculateAverage(long_period_);
    // bool long_avg_greater = CalculateAverage(short_period_) < CalculateAverage(long_period_);
    bool avg_above_price = CalculateAverage(short_period_) > current_records_.back();

    // bool open_condtion = increase_in_row and single_rise and not position_opened;
    // bool close_condition = decrease_in_row and single_fall and position_opened;
    // bool open_condtion = not two_same_prices and not position_opened;
    // bool close_condition = two_same_prices and position_opened;
    bool open_condtion = not avg_above_price and not position_opened;
    bool close_condition = avg_above_price and position_opened;

    if (open_condtion)
    {
        OpenPosition();
    }
    else if (close_condition)
    {
        ClosePosition();
    }
    else
    {
        data_.actions.push_back(action::none);
    }
}

double BotSimulator::CalculateAverage(size_t period) const
{
    size_t number_of_elements = std::min(period, current_records_.size());
    auto first = current_records_.end() - number_of_elements;
    return std::accumulate(first, current_records_.end(), 0.0) / number_of_elements;
}

SimulatedData BotSimulator::GetSimulatedData()
{
    return data_;
}
