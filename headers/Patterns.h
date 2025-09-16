#ifndef BEHAVIOURS_H
#define BEHAVIOURS_H

#include <algorithm>
#include <cstddef>
#include <deque>
#include <functional>
#include <vector>

inline constexpr double percentage_profit = 0.05;
inline constexpr double percentage_loss = 0.05;
inline constexpr double percentage_peak_profit = 1.9;
inline constexpr double percentage_peak_loss = 1.9;

bool IsConstantFall(const std::deque<double>& current_records);
bool IsConstantRise(const std::deque<double>& current_records);
bool IsSuddenFall(const std::deque<double>& current_records);
bool IsSuddenRise(const std::deque<double>& current_records);
bool ShortAvgDecrease(const std::vector<double>& short_averages, size_t price_index);
bool ShortAvgIncrease(const std::vector<double>& short_averages, size_t price_index);
bool ShortAvgDoubleDecrease(const std::vector<double>& short_averages, size_t price_index);
bool ShortAvgDoubleIncrease(const std::vector<double>& short_averages, size_t price_index);
bool IncreasesInRow(const std::vector<double>& short_averages, size_t inc_in_row);
bool DecreasesInRow(const std::vector<double>& short_averages, size_t dec_in_row);
bool TwoSamePriceInRow(const std::deque<double>& current_records);

template<typename Container, typename Compare> bool CheckTendencyInRow(const Container& data, size_t n, Compare comp)
{
    if (data.size() < n + 1)
    {
        return false;
    }

    for (size_t i = 0; i < n; ++i)
    {
        size_t index = data.size() - 1 - i;

        if (!comp(data[index], data[index - 1]))
        {
            return false;
        }
    }
    return true;
}

#endif