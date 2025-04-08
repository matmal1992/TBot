#include "headers\BotSimulator.h"

int main() {
  CsvData data("US500_prices.csv");
  LoadedData prices = data.LoadDataFromFile();
  BotSimulator bot_simulator(prices.prices);
  DiagnosticData diagnostic_data = data.GetDiagnosticData(prices.prices);

  bot_simulator.Iterate();

  std::vector<bool> opens = bot_simulator.GetActions().opens;

  std::cout << "Average Price: " << diagnostic_data.avg_price << std::endl;
  std::cout << "Biggest difference: " << diagnostic_data.biggest_difference
            << std::endl;
  std::cout << "Index of difference: " << std::endl;
  data.PrintGraph(prices, opens);

  return 0;
}
