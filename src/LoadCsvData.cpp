#include "../headers/LoadCsvData.h"

CsvData::CsvData(const std::string& path)
    : path_(path)
{
    ReadDataFromFile();
}

void CsvData::ReadDataFromFile()
{
    std::ifstream file(path_);
    if (!file)
    {
        std::cerr << "Error: Unable to open file.\n";
        return; // to do: better error hadndling
    }

    std::string line;
    std::getline(file, line); // Skip the first line (header)

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date, priceStr;

        std::getline(ss, date, ',');
        std::getline(ss, priceStr, ',');

        double price = std::stod(priceStr);
        prices.push_back(price);
        times.push_back(date);
        // to do: invalid data hadndling
    }

    file.close();
}

void CsvData::PrintGraph(const DiagnosticData& diag_data, const std::vector<bool>& opens,
                         const std::vector<bool>& closes)
{
    std::ofstream tempFile("plot_data.txt");
    std::ofstream highlightOpensFile("highlight_opens_data.txt");
    std::ofstream highlightClosesFile("highlight_closes_data.txt");

    for (size_t i {0}; i < times.size(); ++i)
    {
        tempFile << i << " " << prices.at(i) << "\n";

        if (opens.at(i) == true)
        {
            highlightOpensFile << i << " " << prices.at(i) << "\n";
        }
        if (closes.at(i) == true)
        {
            highlightClosesFile << i << " " << prices.at(i) << "\n";
        }
    }
    tempFile.close();
    highlightOpensFile.close();
    highlightClosesFile.close();

    std::ostringstream titleStream;
    titleStream << "            AVG value: " << diag_data.avg_price
                << "                        AVG diff: " << diag_data.avg_difference
                << "            MAX diff: " << diag_data.biggest_difference
                << "            MAX diff index: " << diag_data.biggest_difference_index
                << "                        AVG dev: " << diag_data.avg_deviation
                << "            MAX dev: " << diag_data.biggest_deviation
                << "            MAX dev index: " << diag_data.biggest_deviation_index;

    // to do: rescale y axis 10x smaller
    std::string command = "start \"\" gnuplot -e \""
                          "set title '"
        + titleStream.str()
        + "'; "
          "set grid; "
          "unset key; "
          "set xtics 1; "
          "plot 'plot_data.txt' using 1:2 with lines, "
          "'highlight_opens_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'green', "
          "'highlight_closes_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'red'; "
          "pause -1\"";

    system(command.c_str());
}

DiagnosticData CsvData::GetDiagnosticData(const std::vector<double>& prices)
{
    DiagnosticData data;

    if (prices.empty())
    {
        std::cerr << "No valid data found.\n";
        return data;
    }

    double sum_of_differences {0}, sum_of_deviations {0}, biggest_difference {0}, sum_of_prices {0},
        biggest_deviation {0};

    for (size_t i {1}; i < prices.size(); ++i)
    {
        double difference
            = prices.at(i) > prices.at(i - 1) ? (prices.at(i) - prices.at(i - 1)) : (prices.at(i - 1) - prices.at(i));

        double deviation = (std::abs(difference) / prices.at(i)) * 100; // abs() probably not necessary everywhere

        sum_of_differences += std::abs(difference);
        sum_of_deviations += std::abs(deviation);
        data.differences.push_back(std::abs(difference));
        data.deviations.push_back(std::abs(deviation));
        sum_of_prices += prices.at(i);

        if (difference > biggest_difference)
        {
            data.biggest_difference = difference;
            data.biggest_difference_index = i;
        }

        if (deviation > biggest_deviation)
        {
            data.biggest_deviation = deviation;
            data.biggest_deviation_index = i;
        }
    }

    data.avg_difference = sum_of_differences / prices.size();
    data.avg_deviation = sum_of_deviations / prices.size();
    data.avg_price = sum_of_prices / prices.size();

    return data;
}