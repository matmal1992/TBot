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

    void PrintLinearGraph(const int graph_type);
    void PrintHistogram(const int histogram_type);

private:
    std::string GetTitle();
    std::string GetCommand(const int graph_type);
    void SetDataCommands();
    void WriteLinearDataToFile(const std::vector<double>& data, const std::string& path);
    void WriteActionsToFile();

    const DiagnosticData diag_data_;
    const std::vector<std::pair<bool, bool>> actions_;
    const std::vector<double> short_avg_, long_avg_, prices_;
    std::string actions_comm_, short_avg_comm_, long_avg_comm_;
};

#endif