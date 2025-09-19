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

// Checks if the last n changes in the container are all in the same direction
template<typename Container, typename Compare> bool ConstantTendency(const Container& data, size_t n, Compare comp)
{
    if (data.size() < n or n < 2)
    {
        return false;
    }

    for (size_t i = data.size() - n; i < data.size() - 1; ++i)
    {
        if (!comp(data[i + 1], data[i]))
            return false;
    }
    return true;
}
} // namespace patterns

#endif