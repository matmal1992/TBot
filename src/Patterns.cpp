#include "..\headers\Patterns.h"

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

bool TwoSamePriceInRow(const std::deque<double>& current_records)
{
    size_t size = current_records.size();
    if (size < 2)
    {
        return false;
    }

    return current_records[size - 1] == current_records[size - 2];
}
