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

bool ShortAvgDecrease(const std::vector<double>& short_averages, size_t price_index)
{
    size_t size = short_averages.size();

    if (size > 1 and (short_averages.at(size - 1) < short_averages.at(size - 2)))
    {
        return true;
    }
    return false;
}

bool ShortAvgIncrease(const std::vector<double>& short_averages, size_t price_index)
{
    size_t size = short_averages.size();

    if (size > 1 and (short_averages.at(size - 1) > short_averages.at(size - 2)))
    {
        return true;
    }
    return false;
}

bool ShortAvgDoubleDecrease(const std::vector<double>& short_averages, size_t price_index)
{
    size_t size = short_averages.size();

    if (size > 2 and (short_averages.at(size - 1) < short_averages.at(size - 2))
        and (short_averages.at(size - 2) < short_averages.at(size - 3)))
    {
        return true;
    }
    return false;
}

bool ShortAvgDoubleIncrease(const std::vector<double>& short_averages, size_t price_index)
{
    size_t size = short_averages.size();

    if (size > 2 and (short_averages.at(size - 1) > short_averages.at(size - 2))
        and (short_averages.at(size - 2) > short_averages.at(size - 3)))
    {
        return true;
    }
    return false;
}

bool DecreasesInRow(const std::vector<double>& num_data, size_t dec_in_row)
{
    if (num_data.size() < dec_in_row)
    {
        return false; // Not enough elements
    }

    auto start_index = num_data.size() - dec_in_row;
    for (size_t i = start_index + 1; i < num_data.size(); ++i)
    {
        if (num_data[i] >= num_data[i - 1])
        {
            return false; // Not strictly decreasing
        }
    }
    return true;
}
bool IncreasesInRow(const std::vector<double>& num_data, size_t inc_in_row)
{
    if (num_data.size() < inc_in_row)
    {
        return false; // Not enough elements
    }

    auto start_index = num_data.size() - inc_in_row;
    for (size_t i = start_index + 1; i < num_data.size(); ++i)
    {
        if (num_data[i] <= num_data[i - 1])
        {
            return false; // Not strictly increasing
        }
    }
    return true;
}
bool TwoSamePriceInRow(const std::deque<double>& current_records)
{
    size_t size = current_records.size();
    if (size < 2)
        return false;

    return current_records[size - 1] == current_records[size - 2];
}
