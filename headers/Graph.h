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

private:
    std::string SetTitle();

    const DiagnosticData diag_data_;
    const std::vector<std::pair<bool, bool>> actions_;
    const std::vector<double> short_avg_, long_avg_;
    const std::vector<double> prices_;
};

#endif