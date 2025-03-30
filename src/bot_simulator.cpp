#include "headers\BotSimulator.h"

BotSimulator::BotSimulator(const std::vector<double> &prices)
    : prices_(prices) {}

int main() {

  CsvData data("US500_prices.csv");
  std::vector<double> prices = data.LoadPrices();

  // Display the result
  std::cout << "Average Price: " << std::fixed << std::setprecision(2)
            << data.GetAvgValue(prices) << "\n";

  std::vector<double> remembered_records;

  for (size_t i{0}; i < prices.size(); ++i) {
    if (remembered_records.size() < 5) {
      remembered_records.push_back(prices.at(i));
    } else {
      // remove the last record;
    }
  }

  return 0;
}

void BotSimulator::AddRecord() {}
void BotSimulator::Buy() {}
void BotSimulator::Sell() {}
void BotSimulator::CheckTrend() {}
