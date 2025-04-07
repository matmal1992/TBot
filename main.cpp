#include "headers\BotSimulator.h"
#include <iomanip>

int main()
{
  CsvData data("US500_prices.csv");
  LoadedData prices = data.LoadDataFromFile();
  BotSimulator bot_simulator(prices.prices);

  bot_simulator.Iterate();

  std::vector<bool> opens = bot_simulator.GetActions().opens;

  std::cout << "Average Price: " << std::fixed << std::setprecision(2)
            << data.GetAvgValue(prices.prices) << "\n";

  data.PrintGraph(prices, opens);

  return 0;
}
