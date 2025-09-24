#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string>

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
const std::string prices {"testing_data/prices_data.txt"};
const std::string opens {"testing_data/highlight_opens_data.txt"};
const std::string closes {"testing_data/highlight_closes_data.txt"};
const std::string short_avg {"testing_data/short_avg_data.txt"};
const std::string long_avg {"testing_data/long_avg_data.txt"};
const std::string histogram_diff {"testing_data/differences_histogram.txt"};
const std::string histogram_dev = {"testing_data/deviations_histogram.txt"};
} // namespace paths
#endif