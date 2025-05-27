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
        // LongAndShortAvgStrategy();
        // SingleRiseAndFall(i);
        ShortAvgTrend(i, 2, 2);
        // ShortAvgTrend(i);
    }
}

void BotSimulator::SingleRiseAndFall(size_t price_index)
{
    if (SingleRise(current_records) and not position_opened)
    {
        data_.actions.push_back(std::pair(true, false));
        position_opened = true;
        data_.opens++;
        open_value = prices_.at(price_index);
    }
    else if (SingleFall(current_records) and position_opened)
    {
        data_.actions.push_back(std::pair(false, true));
        position_opened = false;
        data_.closes++;
        data_.balance += prices_.at(price_index) - open_value - spread;
    }
    else
    {
        data_.actions.push_back(std::pair(false, false));
    }
}

void BotSimulator::ShortAvgTrend(size_t price_index, size_t dec_in_row, size_t inc_in_row)
{
    // try to add some reserve b - more notes in main
    if (IncreasesInRow(data_.short_averages, inc_in_row) and SingleRise(current_records) and not position_opened)
    {
        data_.actions.push_back(std::pair(true, false));
        position_opened = true;
        data_.opens++;
        open_value = prices_.at(price_index);
    }
    else if (DecreasesInRow(data_.short_averages, dec_in_row) and SingleFall(current_records) and position_opened)
    {
        data_.actions.push_back(std::pair(false, true));
        position_opened = false;
        data_.closes++;
        data_.balance += prices_.at(price_index) - open_value - spread;
    }
    else
    {
        data_.actions.push_back(std::pair(false, false));
    }
}

void BotSimulator::LongAndShortAvgStrategy()
{
    if (current_records.size() < long_period_) // add peak check. Reset average or sth, while peak detected
    {
        data_.actions.push_back(std::pair(false, false));
        return;
    }

    if (CalculateAverage(short_period_) > CalculateAverage(long_period_) and not position_opened)
    {
        data_.actions.push_back(std::pair(true, false));
        position_opened = true;
        data_.opens++;
        open_value = current_records.back();
    }
    else if (CalculateAverage(short_period_) < CalculateAverage(long_period_) and position_opened)
    {
        data_.actions.push_back(std::pair(false, true));
        position_opened = false;
        data_.closes++;
        data_.balance += current_records.back() - open_value - spread;
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
