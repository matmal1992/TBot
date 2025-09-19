#ifndef PATTERNS_H
#define PATTERNS_H

#include "Auxiliary.h"
#include <algorithm>
#include <deque>
#include <vector>

namespace patterns
{
struct Thresholds
{
    inline static constexpr double profit = 0.05;
    inline static constexpr double loss = 0.05;
    inline static constexpr double peak_profit = 1.9;
    inline static constexpr double peak_loss = 0.4;
};

// Checks if the last n prices in the container are the same
bool SamePricesInRow(const std::deque<double>& current_records, const size_t n);

// Checks if the last n changes in the container are all in the same direction
template<typename Container, typename Compare>
bool ConstantTendency(const Container& data, const size_t n, const Compare comp)
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

// Checks if the last change in the container is a sudden rise or fall based on predefined thresholds
template<typename Container> bool IsSuddenChange(const Container& data, const change_direction dir)
{
    if (data.size() < 2)
    {
        return false;
    }

    const double prev = data[data.size() - 2];
    const double last = data.back();

    if (dir == change_direction::rise)
    {
        return last > prev * Thresholds::peak_profit;
    }
    else
    {
        return last < prev * Thresholds::peak_loss;
    }
}
} // namespace patterns

#endif