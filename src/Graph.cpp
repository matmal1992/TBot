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
    std::ofstream prices_file("testing_data/prices_data.txt");
    std::ofstream open_points_file("testing_data/highlight_opens_data.txt");
    std::ofstream closes_points_file("testing_data/highlight_closes_data.txt");

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

    std::string command = "start \"\" gnuplot -e \""
                          "set title \\\""
        + SetTitle()
        + "\\\" enhanced; "
          "set grid; "
          "unset key; "
          "plot 'testing_data/prices_data.txt' using 1:2 with lines, "
          "'testing_data/highlight_opens_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'green',"
          "'testing_data/highlight_closes_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'red'; "
          "pause -1\"";

    system(command.c_str());
}

void Graph::PrintAverages()
{
    std::ofstream prices_file("testing_data/prices_data.txt");
    std::ofstream short_avg_file("testing_data/short_avg_data.txt");
    std::ofstream long_avg_file("testing_data/long_avg_data.txt");

    for (size_t i {0}; i < prices_.size(); ++i) { prices_file << i << " " << prices_.at(i) << "\n"; }
    for (size_t i {0}; i < short_avg_.size(); ++i) { short_avg_file << i << " " << short_avg_.at(i) << "\n"; }
    for (size_t i {0}; i < long_avg_.size(); ++i) { long_avg_file << i << " " << long_avg_.at(i) << "\n"; }

    short_avg_file.close();
    long_avg_file.close();
    prices_file.close();

    std::string command = "start \"\" gnuplot -e \""
                          "set title '"
        + SetTitle()
        + "'; "
          "set grid; "
          "unset key; "
          "plot 'testing_data/prices_data.txt' using 1:2 with lines, "
          "'testing_data/short_avg_data.txt' using 1:2 with lines lc rgb 'blue', "
          "'testing_data/long_avg_data.txt' using 1:2 with lines lc rgb 'green'; "
          "pause -1\"";

    system(command.c_str());
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