#include "../headers/LoadCsvData.h"

CsvData::CsvData(const std::string& path, const int time_interval)
    : path_(path)
    , time_interval_(time_interval)
{
    ReadDataFromFile();
}

CsvData::CsvData(const std::vector<double>& test_data)
    : prices_(test_data)
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
                prices_.push_back(price);
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

DiagnosticData CsvData::GetDiagnosticData()
{
    DiagnosticData data;

    if (prices_.empty())
    {
        std::cerr << "No valid data found.\n";
        return data;
    }

    double sum_of_differences {0}, sum_of_deviations {0}, biggest_difference {0}, sum_of_prices {0},
        biggest_deviation {0};

    for (size_t i {1}; i < prices_.size(); ++i)
    {
        double difference = prices_.at(i) > prices_.at(i - 1) ? (prices_.at(i) - prices_.at(i - 1))
                                                              : (prices_.at(i - 1) - prices_.at(i));

        double deviation = ((difference) / prices_.at(i)) * 100;

        sum_of_differences += difference;
        sum_of_deviations += deviation;
        data.differences.push_back(difference);
        data.deviations.push_back(deviation);
        sum_of_prices += prices_.at(i);

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

    data.avg_difference = sum_of_differences / prices_.size();
    data.avg_deviation = sum_of_deviations / prices_.size();
    data.avg_price = sum_of_prices / prices_.size();

    return data;
}

std::vector<double> CsvData::GetPrices()
{
    return prices_;
}

void CsvData::TrimPricesVector(size_t begin, size_t end)
{
    std::vector<double> trimmed_prices(prices_.begin() + begin, prices_.begin() + end);
    prices_ = trimmed_prices;
}