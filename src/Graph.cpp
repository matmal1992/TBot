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

    system(GetCommand(graph_type).c_str());
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

std::string Graph::GetCommand(const int graph_type)
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
    double max_value {0}, bin_size {0};
    int bin_count {0};
    std::string histogram_path, final_command, type, colour;
    std::vector<double> histogram_data;

    if (hist_type == histogram_type::diffs)
    {
        max_value = 1.5;
        bin_size = 0.05;
        histogram_path = paths::histogram_diff;
        histogram_data = diag_data_.differences;
        type = "Difference";
        colour = "skyblue";
    }
    else
    {
        max_value = 0.01;
        bin_size = 0.001;
        histogram_path = paths::histogram_dev;
        histogram_data = diag_data_.deviations;
        type = "Deviation";
        colour = "orange";
    }

    bin_count = static_cast<int>(max_value / bin_size);
    std::vector<int> histogram(bin_count, 0);

    for (double val : histogram_data)
    {
        if (val >= 0.0 and val < max_value)
        {
            int bin_index = static_cast<int>(val / bin_size);
            ++histogram.at(bin_index);
        }
        else if (val >= max_value)
        {
            ++histogram.at(bin_count - 1);
        }
    }

    std::ofstream hist_file(histogram_path);

    for (int i = 0; i < bin_count; ++i)
    {
        double bin_start = i * bin_size;
        double bin_mid = bin_start + bin_size / 2.0;
        hist_file << bin_mid << " " << histogram.at(i) << "\n";
    }

    hist_file.close();

    final_command.append("start \"\" gnuplot -e \"");
    final_command.append("set title '" + type + " histogram'; ");
    final_command.append("set style fill solid; set grid; unset key; ");
    final_command.append("set xlabel '" + type + "'; set ylabel 'Count'; ");
    final_command.append("plot '" + histogram_path + "' using 1:2 with boxes lc rgb '" + colour + "'; ");
    final_command.append("pause -1\"");

    system(final_command.c_str());
}