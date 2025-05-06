#ifndef GRAPH_H
#define GRAPH_H

#include "Auxiliary.h"
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
};

#endif