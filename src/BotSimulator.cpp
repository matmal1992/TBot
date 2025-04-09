#include "..\headers\BotSimulator.h"

BotSimulator::BotSimulator(const std::vector<double>& prices)
    : prices_(prices)
{
}

void BotSimulator::AddRecord(int record_index)
{
    if (current_records.size() < 5)
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
        if (current_records[i] < current_records[i - 1])
        {
            return false;
        }
    }
    return true;
}

bool BotSimulator::IsConstantRise()
{
    for (size_t i = 1; i < current_records.size(); ++i)
    {
        if (current_records[i] > current_records[i - 1])
        {
            return false;
        }
    }
    return true;
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

void BotSimulator::Iterate()
{
    int amount_of_opens {0};

    for (size_t i {0}; i < prices_.size(); ++i)
    {
        AddRecord(i);
        if (/*IsConstantRise() or */ IsSuddenRise())
        {
            actions.opens.push_back(true);
            actions.closes.push_back(false);
            amount_of_opens++;
        }
        else
        {
            actions.opens.push_back(false);
            actions.closes.push_back(false);
        }
        // else if (/*IsConstantFall() or */ IsSuddenFall())
        // {
        //   actions.opens.at(i) = false;
        //   actions.closes.at(i) = true;
        // }
    }
    std::cout << "Size of opens after iteration: " << amount_of_opens << std::endl;
}

Actions BotSimulator::GetActions()
{
    return actions;
}