#include "../headers/LoadCsvData.h"

CsvData::CsvData(const std::string& path, const int time_interval)
    : path_(path)
    , time_interval_(time_interval)
{
    ReadDataFromFile();
}

CsvData::CsvData(const std::vector<double>& test_data)
    : prices(test_data)
{
    if (test_data.empty())
    {
        std::cerr << "No valid data found.\n";
    }
}

void CsvData::ReadDataFromFile()
{
    std::cerr << "Absolute path: " << std::filesystem::absolute(path_) << "\n";
    std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

    if (!std::filesystem::exists(path_))
    {
        std::cerr << "Error: File does not exist at path: " << path_ << "\n";
        return;
    }

    std::ifstream file(path_);
    if (!file)
    {
        std::cerr << "Error: Unable to open file: " << path_ << "\n";
        return; // to do: better error hadndling
    }

    std::string line;
    std::getline(file, line); // Skip the first line (header)

    int counter {0};

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string priceStr;
        std::getline(ss, priceStr);

        try
        {
            double price = std::stod(priceStr);

            if (counter % time_interval_ == 0)
            {
                prices.push_back(price);
                // times.push_back(date); // leave for release
            }
            counter++;
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Warning: Invalid data on line " << counter + 2 << ": " << line << "\n";
            continue; // skip invalid line
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Warning: Out-of-range value on line " << counter + 2 << ": " << line << "\n";
            continue;
        }
    }

    file.close();
}

void CsvData::PrintGraph(const DiagnosticData& diag_data, const std::vector<std::pair<bool, bool>>& actions,
                         const std::vector<double>& avg)
{
    std::ofstream tempFile("data/plot_data.txt");
    std::ofstream highlightOpensFile("data/highlight_opens_data.txt");
    std::ofstream highlightClosesFile("data/highlight_closes_data.txt");

    std::cout << "actions.size(): " << actions.size() << std::endl;
    std::cout << "prices.size(): " << prices.size() << std::endl;

    for (size_t i {0}; i < prices.size() - 4; ++i)
    {
        tempFile << i << " " << prices.at(i) << "\n";

        if (actions.at(i).first == true)
        {
            highlightOpensFile << i << " " << prices.at(i) << "\n";
        }
        if (actions.at(i).second == true)
        {
            highlightClosesFile << i << " " << prices.at(i) << "\n";
        }
    }

    std::ofstream avgFile("data/avg_data.txt");
    for (size_t i = 0; i < avg.size(); ++i) { avgFile << i << " " << avg.at(i) << "\n"; }
    avgFile.close();

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
    // to do: draw short/long period avg lines
    std::string command = "start \"\" gnuplot -e \""
                          "set title '"
        + titleStream.str()
        + "'; "
          "set grid; "
          "unset key; "
          //   "set xtics 1; "
          "plot 'plot_data.txt' using 1:2 with lines, "
          "'data/avg_data.txt' using 1:2 with lines lc rgb 'blue', "
          "'data/highlight_opens_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'green', "
          "'data/highlight_closes_data.txt' using 1:2 with points pointtype 7 pointsize 1.0 lc rgb 'red'; "
          "pause -1\"";

    system(command.c_str());
}

DiagnosticData CsvData::GetDiagnosticData()
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

std::vector<double> CsvData::GetPrices()
{
    return prices;
}

void CsvData::TrimPricesVector(size_t begin, size_t end)
{
    std::vector<double> trimmed_prices(prices.begin() + begin, prices.begin() + end);
    prices = trimmed_prices;
}