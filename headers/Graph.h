#ifndef GRAPH_H
#define GRAPH_H

#include "LoadCsvData.h"
#include <vector>

class Graph
{
public:
    Graph(const DiagnosticData& diag_data, const std::vector<std::pair<bool, bool>>& actions,
          const std::vector<double>& short_avg, const std::vector<double>& long_avg, const std::vector<double>& prices);

    void PrintActions();
    void PrintAverages();
    void PrintActionsAndAvg();
    void PrintDifferencesHistogram();
    void PrintDeviationsHistogram();

private:
    std::string SetTitle();
    std::string SetCommand(const std::string& data_command);

    const DiagnosticData diag_data_;
    const std::vector<std::pair<bool, bool>> actions_;
    const std::vector<double> short_avg_, long_avg_;
    const std::vector<double> prices_;

    const std::string prices_path_ {"testing_data/prices_data.txt"};
    const std::string opens_path_ {"testing_data/highlight_opens_data.txt"};
    const std::string closes_path_ {"testing_data/highlight_closes_data.txt"};
    const std::string short_avg_path_ {"testing_data/short_avg_data.txt"};
    const std::string long_avg_path_ {"testing_data/long_avg_data.txt"};
    const std::string histogram_diff_path = "testing_data/differences_histogram.txt";
    const std::string histogram_dev_path = "testing_data/deviations_histogram.txt";
};

#endif