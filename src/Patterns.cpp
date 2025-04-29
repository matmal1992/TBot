#include "..\headers\Patterns.h"

bool IsConstantFall(const std::deque<double>& current_records)
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

bool IsConstantRise(const std::deque<double>& current_records)
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

bool IsSuddenRise(const std::deque<double>& current_records)
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

bool IsSuddenFall(const std::deque<double>& current_records)
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

bool SingleFall(const std::deque<double>& current_records)
{
    size_t size = current_records.size();

    if (size > 1 and (current_records.at(size - 1) < current_records.at(size - 2)))
    {
        return true;
    }

    return false;
}

bool TwoFallsInRow(const std::deque<double>& current_records)
{
    size_t size = current_records.size();

    if (size > 2 and (current_records.at(size - 1) < current_records.at(size - 2)))
    {
        return true;
    }

    return false;
}

bool SingleRise(const std::deque<double>& current_records)
{
    size_t size = current_records.size();

    if (size > 1 and (current_records.at(size - 1) > current_records.at(size - 2)))
    {
        return true;
    }
    return false;
}

bool TwoRisesInRow(const std::deque<double>& current_records)
{
    size_t size = current_records.size();

    if (size > 2 and (current_records.at(size - 1) > current_records.at(size - 2))
        and (current_records.at(size - 2) > current_records.at(size - 3)))
    {
        return true;
    }
    return false;
}