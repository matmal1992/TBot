#include "..\headers\BotSimulator.h"

BotSimulator::BotSimulator(const std::vector<double>& prices)
    : prices_(prices)
{
    Iterate();
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
bool BotSimulator::SingleFallDetected()
{
    // PrintVector(current_records);

    for (size_t i = 1; i < current_records.size(); ++i)
    {
        if (current_records[i] < current_records[i - 1])
        {
            // std::cout << std::endl << "Single fall detected" << std::endl;
            // std::cout << "current_records[i]: " << current_records[i] << std::endl;
            // std::cout << "current_records[i - 1]: " << current_records[i - 1] << std::endl << std::endl;
            return true;
        }
    }
    return false;
}

bool BotSimulator::SingleRiseDetected()
{
    // PrintVector(current_records);

    for (size_t i = 1; i < current_records.size(); ++i)
    {
        if (current_records[i] > current_records[i - 1])
        {
            // std::cout << std::endl << "Single rise detected" << std::endl;
            // std::cout << "current_records[i]: " << current_records[i] << std::endl;
            // std::cout << "current_records[i - 1]: " << current_records[i - 1] << std::endl << std::endl;
            return true;
        }
    }
    return false;
}

void BotSimulator::Iterate()
{
    for (size_t i {0}; i < prices_.size(); ++i)
    {
        AddRecord(i);
        ActWithSimpleStrategy();
    }
}

void BotSimulator::ActWithSimpleStrategy()
{
    if (SingleRiseDetected() and not position_opened)
    {
        actions.push_back(std::pair(true, false));
        position_opened = true;
    }
    else if (SingleFallDetected() and position_opened)
    {
        actions.push_back(std::pair(false, true));
        position_opened = false;
    }
    else
    {
        actions.push_back(std::pair(false, false));
    }
}

// void BotSimulator::ActWithMoerComplicatedStrategy()
// {
//     if ((IsConstantRise() or IsSuddenRise()) and not position_opened)
//     {
//         opens.push_back(true);
//         closes.push_back(false);
//         position_opened = true;
//     }
//     else if ((IsConstantFall() or IsSuddenFall()) and position_opened)
//     {
//         opens.push_back(false);
//         closes.push_back(true);
//         position_opened = false;
//     }
//     else
//     {
//         opens.push_back(false);
//         closes.push_back(false);
//     }
// }

void BotSimulator::PrintVector(const std::deque<double>& vec)
{
    std::cout << "current_records: ";
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