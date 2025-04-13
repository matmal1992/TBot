#ifndef _LOAD_CSV_DATA_
#define _LOAD_CSV_DATA_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

struct DiagnosticData
{
    std::vector<double> differences;
    double biggest_difference {0};
    double avg_difference {0};

    std::vector<double> deviations;
    double biggest_deviation {0};
    double avg_deviation {0};

    double avg_price {0};
    int biggest_difference_index {0};
    int biggest_deviation_index {0};
};

class CsvData
{
public:
    CsvData(const std::string& path);
    CsvData(const std::vector<double>& test_data);

    DiagnosticData GetDiagnosticData();
    void PrintGraph(const DiagnosticData& diag_data, const std::vector<std::pair<bool, bool>>& actions);
    std::vector<double> GetPrices();

private:
    void ReadDataFromFile();

    std::string path_;
    std::vector<double> prices;
    // std::vector<std::string> times; // for release version
};

#endif
