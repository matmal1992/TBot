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

void Graph::PrintDifferencesHistogram()
{
    const double max_value = 1.5;
    const double bin_size = 0.05;
    const int bin_count = static_cast<int>(max_value / bin_size);
    std::vector<int> histogram(bin_count, 0);

    // Count how many values fall into each bin
    for (double val : diag_data_.differences)
    {
        if (val >= 0.0 and val < max_value)
        {
            int bin_index = static_cast<int>(val / bin_size);
            ++histogram.at(bin_index);
        }
        else if (val >= max_value)
        {
            ++histogram.at(bin_count - 1); // put max values in the last bin
        }
    }

    std::ofstream hist_diff_file(histogram_diff_path);

    for (int i = 0; i < bin_count; ++i)
    {
        double bin_start = i * bin_size;
        double bin_mid = bin_start + bin_size / 2.0;
        hist_diff_file << bin_mid << " " << histogram.at(i) << "\n";
    }

    hist_diff_file.close();

    std::string command = "start \"\" gnuplot -e \""
                          "set title 'Differences Histogram'; "
                          "set boxwidth 0.04; "
                          "set style fill solid; "
                          "set grid; unset key; "
                          "set xlabel 'Difference'; "
                          "set ylabel 'Count'; "
                          "plot '"
        + histogram_diff_path
        + "' using 1:2 with boxes lc rgb 'skyblue'; "
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