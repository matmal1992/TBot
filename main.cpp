#include "headers\LoadCsvData.h"
#include <iomanip>

int main()
{
  CsvData data("US500_prices.csv");
  std::vector<double> prices = data.LoadPrices();

  std::cout << "Average Price: " << std::fixed << std::setprecision(2)
            << data.GetAvgValue(prices) << "\n";

  data.PrintGraph();

  return 0;
}
