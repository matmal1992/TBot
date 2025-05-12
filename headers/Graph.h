#ifndef GRAPH_H
#define GRAPH_H

#include "Auxiliary.h"
#include "LoadCsvData.h"
#include <map>
#include <vector>

struct HistogramConfig
{
    double max_value;
    double bin_size;
    std::string path;
    std::vector<double> data;
    std::string label;
    std::string color;
};

class Graph
{
public:
    Graph(const DiagnosticData& diag_data, const std::vector<std::pair<bool, bool>>& actions,
          const std::vector<double>& short_avg, const std::vector<double>& long_avg, const std::vector<double>& prices);

    void PrintLinearGraph(const int graph_type);
    void PrintHistogram(const int histogram_type);

private:
    std::string GetTitle();
    std::string BuildGraphCommand(const int graph_type);
    std::string BuildHistogramCommand(const std::string& title, const std::string& path, const std::string& color);
    void SetDataCommands();
    void WriteLinearDataToFile(const std::vector<double>& data, const std::string& path);
    void WriteActionsToFile();

    const DiagnosticData diag_data_;
    const std::vector<std::pair<bool, bool>> actions_;
    const std::vector<double> short_avg_, long_avg_, prices_;
    std::string actions_comm_, short_avg_comm_, long_avg_comm_;
};

#endif