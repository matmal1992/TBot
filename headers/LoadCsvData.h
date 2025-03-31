#ifndef _LOAD_CSV_DATA_
#define _LOAD_CSV_DATA_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

class CsvData
{
public:
  CsvData(const std::string &path);
  std::vector<double> LoadPrices();
  double GetAvgValue(std::vector<double> data);
  void PrintGraph();

private:
  std::string path_;
};

#endif
