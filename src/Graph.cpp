#include "../headers/Graph.h"

Graph::Graph(const DiagnosticData& diag_data, const std::vector<std::pair<bool, bool>>& actions,
             const std::vector<double>& short_avg, const std::vector<double>& long_avg,
             const std::vector<double>& prices)
    : diag_data_(diag_data)
    , actions_(actions)
    , short_avg_(short_avg)
    , long_avg_(long_avg)
    , prices_(prices)
{
    SetDataCommands();
}

void Graph::PrintLinearGraph(const int graph_type)
{
    WriteLinearDataToFile(prices_, paths::prices);
    WriteActionsToFile();
    WriteLinearDataToFile(short_avg_, paths::short_avg);
    WriteLinearDataToFile(long_avg_, paths::long_avg);

    system(BuildGraphCommand(graph_type).c_str());
}

void Graph::WriteLinearDataToFile(const std::vector<double>& data, const std::string& path)
{
    std::ofstream file_to_write(path);
    for (size_t i {0}; i < data.size(); ++i) file_to_write << i << " " << data.at(i) << "\n";
    file_to_write.close();
}

void Graph::WriteActionsToFile()
{
    std::ofstream open_points_file(paths::opens);
    std::ofstream closes_points_file(paths::closes);

    for (size_t i {0}; i < prices_.size() - 4; ++i)
    {
        if (actions_.at(i).first == true)
        {
            open_points_file << i << " " << prices_.at(i) << "\n";
        }
        else if (actions_.at(i).second == true)
        {
            closes_points_file << i << " " << prices_.at(i) << "\n";
        }
    }

    open_points_file.close();
    closes_points_file.close();
}

std::string Graph::GetTitle()
{
    std::string title;

    title.append("AVG diff: " + std::to_string(diag_data_.avg_difference)).append(40, ' ');
    title.append("MAX diff: " + std::to_string(diag_data_.biggest_difference)).append(40, ' ');
    title.append("MAX diff index: " + std::to_string(diag_data_.biggest_difference_index) + "\\n");

    title.append("AVG dev: " + std::to_string(diag_data_.avg_deviation)).append(40, ' ');
    title.append("MAX dev: " + std::to_string(diag_data_.biggest_deviation)).append(40, ' ');
    title.append("MAX dev index: " + std::to_string(diag_data_.biggest_deviation_index));
    return title;
}

std::string Graph::BuildGraphCommand(const int graph_type)
{
    std::string data_command;
    switch (graph_type)
    {
        case graph_type::short_avg: data_command = short_avg_comm_ + ", " + long_avg_comm_; break;
        case graph_type::long_avg: data_command = actions_comm_ + ", " + long_avg_comm_; break;
        case graph_type::both_avg: data_command = actions_comm_ + ", " + short_avg_comm_ + ", " + long_avg_comm_; break;
        case graph_type::only_avgs: data_command = short_avg_comm_ + ", " + long_avg_comm_; break;
        case graph_type::only_actions: data_command = actions_comm_; break;
    }

    std::string final_command;
    final_command.append("start \"\" gnuplot -e \"");
    final_command.append("set title \\\"" + GetTitle() + "\\\" enhanced; ");
    final_command.append("set grid; unset key; ");
    final_command.append("plot 'testing_data/prices_data.txt' using 1:2 with lines, ");
    final_command.append(data_command.append("; "));
    final_command.append("pause -1\"");

    return final_command;
}

void Graph::SetDataCommands()
{
    short_avg_comm_ = "'" + paths::short_avg + "' using 1:2 with lines lc rgb 'blue'";
    long_avg_comm_ = "'" + paths::long_avg + "' using 1:2 with lines lc rgb 'green'";
    actions_comm_ = "'" + paths::opens + "' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'green', '"
        + paths::closes + "' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'red'";
}

void Graph::PrintHistogram(const int hist_type)
{
    const std::map<int, HistogramConfig> configs
        = {{histogram_type::diffs, {1.5, 0.05, paths::histogram_diff, diag_data_.differences, "Difference", "skyblue"}},
           {histogram_type::devs, {0.01, 0.001, paths::histogram_dev, diag_data_.deviations, "Deviation", "orange"}}};

    const auto& cfg = configs.at(hist_type);
    int bin_count = static_cast<int>(cfg.max_value / cfg.bin_size);
    std::vector<int> histogram(bin_count, 0);

    for (double val : cfg.data)
    {
        int bin_index = static_cast<int>(std::min(val, cfg.max_value - 1e-9) / cfg.bin_size);
        ++histogram.at(bin_index);
    }

    std::ofstream hist_file(cfg.path);
    for (int i = 0; i < bin_count; ++i)
    {
        double bin_mid = i * cfg.bin_size + cfg.bin_size / 2.0;
        hist_file << bin_mid << " " << histogram[i] << "\n";
    }
    hist_file.close();

    system(BuildHistogramCommand(cfg.label, cfg.path, cfg.color).c_str());
}

std::string Graph::BuildHistogramCommand(const std::string& title, const std::string& path, const std::string& color)
{
    std::string cmd;
    cmd.append("start \"\" gnuplot -e \"");
    cmd.append("set title '" + title + " histogram'; ");
    cmd.append("set style fill solid; set grid; unset key; ");
    cmd.append("set xlabel '" + title + "'; set ylabel 'Count'; ");
    cmd.append("plot '" + path + "' using 1:2 with boxes lc rgb '" + color + "'; ");
    cmd.append("pause -1\"");
    return cmd;
}