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
class CsvData
{
public:
  CsvData(const std::string &path);
  LoadedData LoadDataFromFile();
  double GetAvgValue(std::vector<double> data);
  void PrintGraph(const LoadedData &data);

private:
  std::string path_;
};

#endif
