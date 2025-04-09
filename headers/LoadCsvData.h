#ifndef _LOAD_CSV_DATA_
#define _LOAD_CSV_DATA_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

struct LoadedData
{
    std::vector<double> prices;
    std::vector<std::string> times;
};

struct DiagnosticData
{
    std::vector<double> deviations;
    std::vector<double> differences;
    double biggest_difference {}; // done
    double avg_difference {};
    double biggest_deviation {};
    double avg_deviation {};
    double avg_price {};
};

class CsvData
{
public:
    CsvData(const std::string& path);

    LoadedData LoadDataFromFile();
    DiagnosticData GetDiagnosticData(const std::vector<double>& prices);
    void PrintGraph(const LoadedData& data, const std::vector<bool>& opens);

private:
    double GetAvgValue(const std::vector<double>& num_data);
    double GetBiggestDifference(const std::vector<double>& num_data);
    double GetAvgDifference(const std::vector<double>& num_data);
    std::string path_;
};

#endif
