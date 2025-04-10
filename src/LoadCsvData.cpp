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

        if (std::abs(difference) > biggest_difference)
        {
            biggest_difference = difference;
            data.biggest_difference_index = i;
        }

        if (deviation > biggest_deviation)
        {
            biggest_deviation = deviation;
            data.biggest_deviation_index = i;
        }
    }

    data.avg_difference = sum_of_differences / prices.size();
    data.avg_deviation = sum_of_deviations / prices.size();
    data.avg_price = sum_of_prices / prices.size();

    return data;
}