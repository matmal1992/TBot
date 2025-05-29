#include "..\headers\BotSimulator.h"

BotSimulator::BotSimulator(const std::vector<double>& prices, const int short_period, const int long_period)
    : prices_(prices)
    , short_period_(short_period)
    , long_period_(long_period)
{
    Iterate();
}

void BotSimulator::AddRecord(int record_index)
{
    if (current_records.size() < long_period_)
    {
        current_records.push_back(prices_.at(record_index));
    }
    else
    {
        current_records.pop_front();
        current_records.push_back(prices_.at(record_index));
    }

    data_.short_averages.push_back(CalculateAverage(short_period_));
    data_.long_averages.push_back(CalculateAverage(long_period_));
}

void BotSimulator::Iterate()
{
    for (size_t i {0}; i < prices_.size(); ++i)
    {
        AddRecord(i);
        MakeDecision();
    }
}

void BotSimulator::OpenPosition()
{
    data_.actions.push_back(std::pair(true, false));
    position_opened = true;
    data_.opens++;
    open_value = current_records.back();
}

void BotSimulator::ClosePOsition()
{
    data_.actions.push_back(std::pair(false, true));
    position_opened = false;
    data_.closes++;
    data_.balance += current_records.back() - open_value - spread;
}

void BotSimulator::MakeDecision()
{
    bool single_rise = SingleRise(current_records);
    bool single_fall = SingleFall(current_records);
    bool increase_in_row = IncreasesInRow(data_.short_averages, 2);
    bool decrease_in_row = DecreasesInRow(data_.short_averages, 2);
    bool short_avg_greater = CalculateAverage(short_period_) > CalculateAverage(long_period_);
    bool long_avg_greater = CalculateAverage(short_period_) < CalculateAverage(long_period_);

    bool open_condtion = increase_in_row and single_rise and not position_opened;
    bool close_condition = decrease_in_row and single_fall and position_opened;

    if (open_condtion)
    {
        OpenPosition();
    }
    else if (close_condition)
    {
        ClosePOsition();
    }
    else
    {
        data_.actions.push_back(std::pair(false, false));
    }
}

double BotSimulator::CalculateAverage(size_t period)
{
    if (current_records.size() < period)
    {
        return std::accumulate(current_records.begin(), current_records.end(), 0.0) / current_records.size();
    }
    else
    {
        return std::accumulate(current_records.end() - period, current_records.end(), 0.0) / period;
    }
}

SimulatedData BotSimulator::GetSimulatedData()
{
    return data_;
}
