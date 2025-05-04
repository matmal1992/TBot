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
}

void Graph::PrintActions()
{
    std::ofstream prices_file(prices_path_);
    std::ofstream open_points_file(opens_path_);
    std::ofstream closes_points_file(closes_path_);

    for (size_t i {0}; i < prices_.size() - 4; ++i)
    {
        prices_file << i << " " << prices_.at(i) << "\n";

        if (actions_.at(i).first == true)
        {
            open_points_file << i << " " << prices_.at(i) << "\n";
        }
        if (actions_.at(i).second == true)
        {
            closes_points_file << i << " " << prices_.at(i) << "\n";
        }
    }

    prices_file.close();
    open_points_file.close();
    closes_points_file.close();

    std::string opens_data = "'" + opens_path_ + "' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'green',";
    std::string closes_data = "'" + closes_path_ + "' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'red'; ";
    system(SetCommand(opens_data, closes_data).c_str());
}

void Graph::PrintAverages()
{
    std::ofstream prices_file(prices_path_);
    std::ofstream short_avg_file(short_avg_path_);
    std::ofstream long_avg_file(long_avg_path_);

    for (size_t i {0}; i < prices_.size(); ++i) { prices_file << i << " " << prices_.at(i) << "\n"; }
    for (size_t i {0}; i < short_avg_.size(); ++i) { short_avg_file << i << " " << short_avg_.at(i) << "\n"; }
    for (size_t i {0}; i < long_avg_.size(); ++i) { long_avg_file << i << " " << long_avg_.at(i) << "\n"; }

    short_avg_file.close();
    long_avg_file.close();
    prices_file.close();

    std::string short_avg = "'" + short_avg_path_ + "' using 1:2 with lines lc rgb 'blue',";
    std::string long_avg = "'" + long_avg_path_ + "' using 1:2 with lines lc rgb 'green'; ";
    system(SetCommand(short_avg, long_avg).c_str());
}

std::string Graph::SetTitle()
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

std::string Graph::SetCommand(const std::string& data_to_print_1, const std::string& data_to_print_2)
{
    std::string command;

    command.append("start \"\" gnuplot -e \"");
    command.append("set title \\\"" + SetTitle() + "\\\" enhanced; ");
    command.append("set grid; unset key; ");
    command.append("plot 'testing_data/prices_data.txt' using 1:2 with lines, ");
    command.append(data_to_print_1);
    command.append(data_to_print_2);
    command.append("pause -1\"");

    return command;
}