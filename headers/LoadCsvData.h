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
    double biggest_difference {};
    double avg_difference {};

    std::vector<double> deviations;
    double biggest_deviation {};
    double avg_deviation {};

    double avg_price {};
    int biggest_difference_index {0};
    int biggest_deviation_index {0};
};

class CsvData
{
public:
    CsvData(const std::string& path);

    DiagnosticData GetDiagnosticData(const std::vector<double>& prices);
    void PrintGraph(const DiagnosticData&, const std::vector<bool>& opens, const std::vector<bool>& closes);

private:
    void ReadDataFromFile();

    std::string path_;
    std::vector<double> prices;
    std::vector<std::string> times;
};

#endif
