#include "../headers/Graph.h"

Graph::Graph(const DiagnosticData& diag_data, const std::vector<std::pair<bool, bool>>& actions,
             const std::vector<double>& avg, const std::vector<double>& prices)
    : diag_data_(diag_data)
    , actions_(actions)
    , average_(avg)
    , prices_(prices)
{
}

void Graph::PrintActions()
{
    std::ofstream tempFile("testing_data/plot_data.txt");
    std::ofstream highlightOpensFile("testing_data/highlight_opens_data.txt");
    std::ofstream highlightClosesFile("testing_data/highlight_closes_data.txt");

    std::cout << "actions.size(): " << actions_.size() << std::endl;
    std::cout << "prices.size(): " << prices_.size() << std::endl;

    for (size_t i {0}; i < prices_.size() - 4; ++i)
    {
        tempFile << i << " " << prices_.at(i) << "\n";

        if (actions_.at(i).first == true)
        {
            highlightOpensFile << i << " " << prices_.at(i) << "\n";
        }
        if (actions_.at(i).second == true)
        {
            highlightClosesFile << i << " " << prices_.at(i) << "\n";
        }
    }

    std::ofstream avgFile("testing_data/avg_data.txt");
    for (size_t i = 0; i < average_.size(); ++i) { avgFile << i << " " << average_.at(i) << "\n"; }
    avgFile.close();

    tempFile.close();
    highlightOpensFile.close();
    highlightClosesFile.close();

    std::ostringstream titleStream;
    titleStream << "            AVG value: " << diag_data_.avg_price
                << "                        AVG diff: " << diag_data_.avg_difference
                << "            MAX diff: " << diag_data_.biggest_difference
                << "            MAX diff index: " << diag_data_.biggest_difference_index
                << "                        AVG dev: " << diag_data_.avg_deviation
                << "            MAX dev: " << diag_data_.biggest_deviation
                << "            MAX dev index: " << diag_data_.biggest_deviation_index;

    // to do: rescale y axis 10x smaller
    // to do: draw short/long period avg lines
    std::string command = "start \"\" gnuplot -e \""
                          "set title '"
        + titleStream.str()
        + "'; "
          "set grid; "
          "unset key; "
          //   "set xtics 1; "
          "plot 'plot_data.txt' using 1:2 with lines, "
          "'testing_data/avg_data.txt' using 1:2 with lines lc rgb 'blue', "
          "'testing_data/highlight_opens_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'green', "
          "'testing_data/highlight_closes_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'red'; "
          "pause -1\"";

    system(command.c_str());
}