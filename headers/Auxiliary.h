#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string>

struct Config
{
    const size_t short_period {10};
    const size_t long_period {24};
    const size_t time_interval {1};
    const size_t trim_start {3000};
    const size_t trim_end {6000};
    const std::string data_file {"testing_data/eth.csv"};
};

enum class graph_type
{
    short_avg_actions = 1,
    long_avg_actions = 2,
    both_avg_actions = 3,
    only_avgs = 4,
    only_actions = 5
};

enum class direction
{
    rise = 1,
    fall = 2
};

enum class action
{
    none = 0,
    open = 1,
    close = 2
};

enum class histogram_type
{
    diffs = 1,
    devs = 2
};

namespace paths
{
inline constexpr const char* prices = "testing_data/prices_data.txt";
inline constexpr const char* opens = "testing_data/highlight_opens_data.txt";
inline constexpr const char* closes = "testing_data/highlight_closes_data.txt";
inline constexpr const char* short_avg = "testing_data/short_avg_data.txt";
inline constexpr const char* long_avg = "testing_data/long_avg_data.txt";
inline constexpr const char* histogram_diff = "testing_data/differences_histogram.txt";
inline constexpr const char* histogram_dev = "testing_data/deviations_histogram.txt";
} // namespace paths
#endif