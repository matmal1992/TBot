#include "headers\BotSimulator.h"
#include "headers\LoadCsvData.h"
#include <iomanip>


int main() {
  CsvData data("US500_prices.csv");
  std::vector<double> prices = data.LoadPrices();

  data.PrintGraph();

  std::cout << "Average Price: " << std::fixed << std::setprecision(2)
            << data.GetAvgValue(prices) << "\n";

  //   std::vector<double> remembered_records;

  //   for (size_t i{0}; i < prices.size(); ++i) {
  //     if (remembered_records.size() < 5) {
  //       remembered_records.push_back(prices.at(i));
  //     } else {
  //       // remove the last record;
  //     }
  //   }

  // Write data to a temporary file for gnuplot
  //   std::ofstream tempFile("plot_data.txt");
  //   for (size_t i = 0; i < time.size(); i++) {
  //     tempFile << i << " " << price[i]
  //              << "\n"; // Use index instead of time for x-axis
  //   }
  //   tempFile.close();

  //   // Generate gnuplot command
  //   std::string command = "gnuplot -e \"plot 'plot_data.txt' using 1:2 with "
  //                         "lines title 'US500 Price'; pause -1\"";
  //   system(command.c_str());

  return 0;
}
