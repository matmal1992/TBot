#ifndef GRAPH_H
#define GRAPH_H

#include "LoadCsvData.h"
// #include "Patterns.h"
// #include <deque>
// #include <numeric>
#include <vector>

class Graph
{
public:
    Graph(const DiagnosticData& diag_data, const std::vector<std::pair<bool, bool>>& actions,
          const std::vector<double>& avg, const std::vector<double>& prices);

    void PrintActions();
    void PrintAverages();

    std::vector<std::pair<bool, bool>> GetActions();
    std::vector<double> GetLongAvg();
    std::vector<double> GetShortAvg();
    double GetBalance();

private:
    const DiagnosticData diag_data_;
    const std::vector<std::pair<bool, bool>> actions_;
    const std::vector<double> average_;
    const std::vector<double> prices_;
};

#endif