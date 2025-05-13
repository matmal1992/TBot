#include "../headers/LoadCsvData.h"

CsvData::CsvData(const std::string& path, const int time_interval)
    : path_(path)
{
    ReadDataFromFile(time_interval);
}

CsvData::CsvData(const std::vector<double>& test_data)
{
    data_.prices = test_data;
    if (test_data.empty())
    {
        std::cerr << "No valid data found.\n";
    }
}

void CsvData::ReadDataFromFile(const int time_interval)
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

            if (counter % time_interval == 0)
            {
                data_.prices.push_back(price);
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

void CsvData::SetDiagnosticData()
{

    if (data_.prices.empty())
    {
        std::cerr << "No valid data found.\n";
        return;
    }

    double sum_of_differences {0}, sum_of_deviations {0}, biggest_difference {0}, sum_of_prices {0},
        biggest_deviation {0};

    for (size_t i {1}; i < data_.prices.size(); ++i)
    {
        double difference = data_.prices.at(i) > data_.prices.at(i - 1) ? (data_.prices.at(i) - data_.prices.at(i - 1))
                                                                        : (data_.prices.at(i - 1) - data_.prices.at(i));

        double deviation = ((difference) / data_.prices.at(i)) * 100;

        sum_of_differences += difference;
        sum_of_deviations += deviation;
        data_.differences.push_back(difference);
        data_.deviations.push_back(deviation);
        sum_of_prices += data_.prices.at(i);

        if (difference > biggest_difference)
        {
            data_.biggest_difference = difference;
            data_.biggest_difference_index = i;
        }

        if (deviation > biggest_deviation)
        {
            data_.biggest_deviation = deviation;
            data_.biggest_deviation_index = i;
        }
    }

    data_.avg_difference = sum_of_differences / data_.prices.size();
    data_.avg_deviation = sum_of_deviations / data_.prices.size();
    data_.avg_price = sum_of_prices / data_.prices.size();
}

DiagnosticData CsvData::GetDiagnosticData()
{
    return data_;
}

void CsvData::TrimPricesVector(size_t begin, size_t end)
{
    std::vector<double> trimmed_prices(data_.prices.begin() + begin, data_.prices.begin() + end);
    data_.prices = trimmed_prices;
}