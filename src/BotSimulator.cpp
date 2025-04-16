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

bool BotSimulator::IsConstantFall()
{
    for (size_t i = 1; i < current_records.size(); ++i)
    {
        if (current_records[i] < current_records[i - 1] and current_records[i - 1] < current_records[i - 2])
        {
            return true;
        }
    }
    return false;
}

bool BotSimulator::IsConstantRise()
{
    for (size_t i = 2; i < current_records.size(); ++i)
    {
        if (current_records[i] > current_records[i - 1] and current_records[i - 1] > current_records[i - 2])
        {
            return true;
        }
    }
    return false;
}

bool BotSimulator::IsSuddenRise()
{
    for (size_t i = 1; i < current_records.size(); ++i)
    {
        if (current_records[current_records.size() - 1]
            > current_records[current_records.size() - 2] * percentage_peak_profit)
        {
            return true;
        }
    }
    return false;
}

bool BotSimulator::IsSuddenFall()
{
    for (size_t i = 1; i < current_records.size(); ++i)
    {
        if (current_records[i] > current_records[i - 1] * percentage_peak_profit)
        {
            return true;
        }
    }
    return false;
}

bool BotSimulator::SingleFall()
{
    size_t size = current_records.size();

    if (size > 1 and (current_records.at(size - 1) < current_records.at(size - 2)))
    {
        return true;
    }

    return false;
}

bool BotSimulator::TwoFallsInRow()
{
    size_t size = current_records.size();

    if (size > 2 and (current_records.at(size - 1) < current_records.at(size - 2)))
    {
        return true;
    }

    return false;
}

bool BotSimulator::SingleRise()
{
    size_t size = current_records.size();

    if (size > 1 and (current_records.at(size - 1) > current_records.at(size - 2)))
    {
        return true;
    }
    return false;
}

bool BotSimulator::TwoRisesInRow()
{
    size_t size = current_records.size();

    if (size > 2 and (current_records.at(size - 1) > current_records.at(size - 2))
        and (current_records.at(size - 2) > current_records.at(size - 3)))
    {
        return true;
    }
    return false;
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
    if (SingleRise() and not position_opened)
    {
        actions.push_back(std::pair(true, false));
        position_opened = true;
        open_value = prices_.at(price_index);
    }
    else if (SingleFall() and position_opened)
    {
        actions.push_back(std::pair(false, true));
        position_opened = false;
        balance += prices_.at(price_index) - open_value;
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

    if (current_records.size() < long_period_) // add peak check. Reset average or sth, while peak detected
    {
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
        balance += current_records.back() - open_value;
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
        return 0.0;
    }
    else
    {
        return std::accumulate(current_records.end() - period, current_records.end(), 0.0) / period;
    }
}
