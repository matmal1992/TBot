#include "headers\LoadCsvData.h"
#include <iomanip>

int main()
{
  CsvData data("US500_prices.csv");
  LoadedData prices = data.LoadDataFromFile();

  std::cout << "Average Price: " << std::fixed << std::setprecision(2)
            << data.GetAvgValue(prices.prices) << "\n";

  data.PrintGraph(prices);

  return 0;
}
