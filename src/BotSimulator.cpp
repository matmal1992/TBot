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
}

void BotSimulator::Iterate()
{
    for (size_t i {0}; i < prices_.size(); ++i)
    {
        AddRecord(i);
        // ActWithSimpleStrategy(i);
        ActWithLongAndShortStrategy();
    }
}

void BotSimulator::ActWithSimpleStrategy(size_t price_index)
{
    if (SingleRise(current_records) and not position_opened)
    {
        actions.push_back(std::pair(true, false));
        position_opened = true;
        open_value = prices_.at(price_index);
    }
    else if (SingleFall(current_records) and position_opened)
    {
        actions.push_back(std::pair(false, true));
        position_opened = false;
        balance += prices_.at(price_index) - open_value - spread;
    }
    else
    {
        actions.push_back(std::pair(false, false));
    }
}

void BotSimulator::ActWithLongAndShortStrategy()
{
    double short_period_avg = CalculateAverage(short_period_);
    double long_period_avg = CalculateAverage(long_period_);

    short_averages_.push_back(short_period_avg);
    long_averages_.push_back(long_period_avg);

    if (current_records.size() < long_period_) // add peak check. Reset average or sth, while peak detected
    {
        actions.push_back(std::pair(false, false));
        return;
    }

    if (short_period_avg > long_period_avg and not position_opened)
    {
        actions.push_back(std::pair(true, false));
        position_opened = true;
        open_value = current_records.back();
    }
    else if (short_period_avg < long_period_avg and position_opened)
    {
        actions.push_back(std::pair(false, true));
        position_opened = false;
        balance += current_records.back() - open_value - spread;
    }
    else
    {
        actions.push_back(std::pair(false, false));
    }
}

void BotSimulator::PrintVector(const std::deque<double>& vec)
{
    std::cout << std::endl << "current_records: ";
    for (auto c : vec)
    {
        std::cout << c;
        std::cout << " ";
    }
    std::cout << std::endl;
}

std::vector<std::pair<bool, bool>> BotSimulator::GetActions()
{
    return actions;
}

double BotSimulator::GetBalance()
{
    return balance;
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

std::vector<double> BotSimulator::GetLongAvg()
{
    return long_averages_;
}

std::vector<double> BotSimulator::GetShortAvg()
{
    return short_averages_;
}
