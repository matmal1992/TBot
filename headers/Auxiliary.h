#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string>

namespace graph_type
{
// to refactor: bitset or sth
const int short_avg = 1;
const int long_avg = 2;
const int both_avg = 3;
const int only_avgs = 4;
const int only_actions = 5;
} // namespace graph_type

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