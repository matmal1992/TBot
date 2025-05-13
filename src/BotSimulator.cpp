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
        // ActWithLongAndShortStrategy();
        ActWithSingleAvgStrategy(i);
    }
}

void BotSimulator::ActWithSimpleStrategy(size_t price_index)
{
    if (SingleRise(current_records) and not position_opened)
    {
        data_.actions.push_back(std::pair(true, false));
        position_opened = true;
        open_value = prices_.at(price_index);
    }
    else if (SingleFall(current_records) and position_opened)
    {
        data_.actions.push_back(std::pair(false, true));
        position_opened = false;
        balance += prices_.at(price_index) - open_value - spread;
    }
    else
    {
        data_.actions.push_back(std::pair(false, false));
    }
}

void BotSimulator::ActWithSingleAvgStrategy(size_t price_index)
{
    double short_period_avg = CalculateAverage(short_period_);

    data_.short_averages.push_back(short_period_avg);

    if (current_records.size() < short_period_) // add peak check. Reset average or sth, while peak detected
    {
        data_.actions.push_back(std::pair(false, false));
        return;
    }

    // try to add some reserve
    if (short_period_avg <= prices_.at(price_index) and not position_opened)
    {
        data_.actions.push_back(std::pair(true, false));
        position_opened = true;
        open_value = current_records.back();
    }
    else if (short_period_avg > prices_.at(price_index) and position_opened)
    {
        data_.actions.push_back(std::pair(false, true));
        position_opened = false;
        balance += current_records.back() - open_value - spread;
    }
    else
    {
        data_.actions.push_back(std::pair(false, false));
    }
}

void BotSimulator::ActWithLongAndShortStrategy()
{
    double short_period_avg = CalculateAverage(short_period_);
    double long_period_avg = CalculateAverage(long_period_);

    data_.short_averages.push_back(short_period_avg);
    data_.long_averages.push_back(long_period_avg);

    if (current_records.size() < long_period_) // add peak check. Reset average or sth, while peak detected
    {
        data_.actions.push_back(std::pair(false, false));
        return;
    }

    if (short_period_avg > long_period_avg and not position_opened)
    {
        data_.actions.push_back(std::pair(true, false));
        position_opened = true;
        open_value = current_records.back();
    }
    else if (short_period_avg < long_period_avg and position_opened)
    {
        data_.actions.push_back(std::pair(false, true));
        position_opened = false;
        balance += current_records.back() - open_value - spread;
    }
    else
    {
        data_.actions.push_back(std::pair(false, false));
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

SimulatedData BotSimulator::GetSimulatedData()
{
    return data_;
}
