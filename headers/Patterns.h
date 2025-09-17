#ifndef PATTERNS_H
#define PATTERNS_H

#include <algorithm>
#include <deque>
#include <functional>
#include <vector>

namespace patterns
{
inline constexpr double percentage_profit = 0.05;
inline constexpr double percentage_loss = 0.05;
inline constexpr double percentage_peak_profit = 1.9;
inline constexpr double percentage_peak_loss = 0.4;

bool IsSuddenFall(const std::deque<double>& current_records);
bool IsSuddenRise(const std::deque<double>& current_records);
bool TwoSamePricesInRow(const std::deque<double>& current_records);

template<typename Container, typename Compare> bool ConstantTendency(const Container& data, size_t n, Compare comp)
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

/* Implementation, which checks only last n elements of the container. To consider later if will be needed.

template<typename Container, typename Compare>
bool ConstantTendency(const Container& data, size_t n, Compare comp)
{
    if (data.size() < n + 1) return false;

    for (size_t i = 0; i < n; ++i)
    {
        if (!comp(data[data.size() - n + i], data[data.size() - n + i - 1]))
        {
            return false;
        }
    }
    return true;
}*/
} // namespace patterns

#endif