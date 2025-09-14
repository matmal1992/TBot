#include "..\headers\Patterns.h"

bool IsConstantFall(const std::deque<double>& current_records)
{
    if (current_records.size() < 3)
    {
        return false;
    }

    for (size_t i = 2; i < current_records.size(); ++i)
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
    if (current_records.size() < 3)
    {
        return false;
    }

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

template<typename Container, typename Compare> bool CheckTendencyInRow(const Container& data, size_t n, Compare comp)
{
    if (data.size() < n + 1)
    {
        return false;
    }

    for (size_t i = 0; i < n; ++i)
    {
        size_t index = data.size() - 1 - index;

        if (!comp(data[index], data[index - 1]))
        {
            return false;
        }
    }
    return true;
}

bool ShortAvgDecrease(const std::vector<double>& short_averages, size_t /*unused*/)
{
    return CheckTendencyInRow(short_averages, 1, std::less<>());
}

bool ShortAvgIncrease(const std::vector<double>& short_averages, size_t /*unused*/)
{
    return CheckTendencyInRow(short_averages, 1, std::greater<>());
}

bool ShortAvgDoubleDecrease(const std::vector<double>& short_averages, size_t /*unused*/)
{
    return CheckTendencyInRow(short_averages, 2, std::less<>());
}

bool ShortAvgDoubleIncrease(const std::vector<double>& short_averages, size_t /*unused*/)
{
    return CheckTendencyInRow(short_averages, 2, std::greater<>());
}

bool DecreasesInRow(const std::vector<double>& num_data, size_t dec_in_row)
{
    return CheckTendencyInRow(num_data, dec_in_row, std::less<>());
}
bool IncreasesInRow(const std::vector<double>& num_data, size_t inc_in_row)
{
    return CheckTendencyInRow(num_data, inc_in_row, std::greater<>());
}
bool TwoSamePriceInRow(const std::deque<double>& current_records)
{
    size_t size = current_records.size();
    if (size < 2)
        return false;

    return current_records[size - 1] == current_records[size - 2];
}
