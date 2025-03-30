#include "../headers/BotSimulator.h"

BotSimulator::BotSimulator(const std::vector<double> &prices)
    : prices_(prices) {}

void BotSimulator::RunSimulator() {
  for (size_t i{0}; i < prices_.size(); ++i) {
    AddRecord(i);
  }
}

void BotSimulator::AddRecord(int price_index) {
  if (current_records.size() < amount_of_current_records) {
    current_records.push_back(prices_.at(price_index));
  } else {
    current_records.pop_back();
    current_records.push_front(prices_.at(price_index));
  }
}

void BotSimulator::Buy() {}
void BotSimulator::Sell() {}
void BotSimulator::CheckTrend() {}
