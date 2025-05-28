#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string>

enum class graph_type
{
    short_avg = 1,
    long_avg = 2,
    both_avg = 3,
    only_avgs = 4,
    only_actions = 5
};

namespace histogram_type
{
const int diffs = 1;
const int devs = 2;
} // namespace histogram_type

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