#include "../headers/LoadCsvData.h"

CsvData::CsvData(const std::string& path)
    : path_(path)
{
    ;
}

LoadedData CsvData::LoadDataFromFile()
{
    LoadedData data;

    std::ifstream file(path_);
    if (!file)
    {
        std::cerr << "Error: Unable to open file.\n";
        return data; // to do: better error hadndling
    }

    std::string line;

    // Skip the first line (header)
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date, priceStr;

        std::getline(ss, date, ','); // Read first column (date)
        std::getline(ss, priceStr, ','); // Read second column (price)

        double price = std::stod(priceStr);
        data.prices.push_back(price);
        data.times.push_back(date);
        // to do: invalid data hadndling
    }

    file.close();
    return data;
}

void CsvData::PrintGraph(const LoadedData& data, const std::vector<bool>& opens)
{
    // Write data to a temporary file for gnuplot
    std::ofstream tempFile("plot_data.txt");
    std::ofstream highlightFile("highlight_data.txt"); // New file for markers

    for (size_t i = 0; i < data.times.size(); ++i)
    {
        tempFile << i << " " << data.prices[i] << "\n"; // Use index instead of time for x-axis

        // Save every 60th point for highlighting
        if (opens.at(i) == true)
        {
            highlightFile << i << " " << data.prices[i] << "\n";
        }
    }
    tempFile.close();
    highlightFile.close();

    // Generate gnuplot command with markers
    std::string command = "gnuplot -e \""
                          "set title 'US500 Price'; "
                          "set grid; "
                          "plot 'plot_data.txt' using 1:2 with lines title 'Price', "
                          "'highlight_data.txt' using 1:2 with points pointtype 7 pointsize 1.5 lc "
                          "rgb 'green' title '60-min Markers'; "
                          "pause -1\"";
    system(command.c_str());
}

double CsvData::GetAvgValue(const std::vector<double>& num_data)
{
    if (num_data.empty())
    {
        std::cerr << "No valid data found.\n";
        return 0;
    }

    double sum {0};
    for (double num : num_data) { sum += num; }

    double average = sum / num_data.size();
    return average;
}

double CsvData::GetBiggestDifference(const std::vector<double>& num_data)
{
    if (num_data.empty())
    {
        std::cerr << "No valid data found.\n";
        return 0;
    }

    std::vector<double> differences;

    double difference {0}, tmp_difference {0};
    int index {0};

    for (size_t i {1}; i < num_data.size(); ++i)
    {
        double diff = num_data.at(i) > num_data.at(i - 1) ? num_data.at(i) - num_data.at(i - 1)
                                                          : num_data.at(i - 1) - num_data.at(i);

        differences.push_back(std::abs(diff));
        if (std::abs(diff) > difference)
        {
            difference = diff;
            index = i; // move biggest diff and its index to separate struct
        }
    }

    return difference;
}

double CsvData::GetAvgDifference(const std::vector<double>& num_data)
{
    if (num_data.empty())
    {
        std::cerr << "No valid data found.\n";
        return 0;
    }

    double sum_of_differences {0}, difference {0};

    for (size_t i {1}; i < num_data.size(); ++i)
    {
        difference = num_data.at(i) > num_data.at(i - 1) ? num_data.at(i) - num_data.at(i - 1)
                                                         : num_data.at(i - 1) - num_data.at(i);
        sum_of_differences += std::abs(difference);
    }

    double diff_avg = sum_of_differences / num_data.size();
    return diff_avg;
}

DiagnosticData CsvData::GetDiagnosticData(const std::vector<double>& prices)
{
    DiagnosticData data;
    data.avg_price = GetAvgValue(prices);
    data.biggest_difference = GetBiggestDifference(prices);
    data.avg_difference = GetAvgDifference(prices);

    return data;
}