#include "..\headers\Patterns.h"

namespace patterns
{
bool IsSuddenRise(const std::deque<double>& current_records)
{

    if (current_records.size() < 2)
    {
        return false;
    }
    return current_records.back() > current_records[current_records.size() - 2] * percentage_peak_profit;
}

bool IsSuddenFall(const std::deque<double>& current_records)
{
    if (current_records.size() < 2)
    {
        return false;
    }
    return current_records.back() < current_records[current_records.size() - 2] * percentage_peak_loss;
}

bool TwoSamePricesInRow(const std::deque<double>& current_records)
{
    size_t size = current_records.size();
    if (size < 2)
    {
        return false;
    }

    return current_records[size - 1] == current_records[size - 2];
}
} // namespace patterns