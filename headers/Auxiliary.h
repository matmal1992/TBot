#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <string>

namespace graph_type
{
const int no_avg = 1;
const int short_avg = 2;
const int long_avg = 3;
const int both_avg = 4;
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