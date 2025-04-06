#ifndef BOT_SIMULATOR_H
#define BOT_SIMULATOR_H

#include "LoadCsvData.h"
#include <deque>

class BotSimulator
{
public:
  BotSimulator(const std::vector<double> &prices);
  BotSimulator();

private:
  void AddRecord(int record_index);
  void CheckTrend();
  void Buy();
  void Sell();
  bool IsConstantFall();
  bool IsConstantRise();
  bool IsSuddenFall();
  bool IsSuddenRise();

  std::vector<double> prices_;
  std::deque<double> current_records;
  size_t amount_of_current_records = 5;
  double percentage_profit = 0.05;
  double percentage_loss = 0.05;
  double percentage_peak_profit = 0.2;
  double percentage_peak_loss = 0.2;
  size_t investing_value = 5000;

  double balance{0};
  size_t buys{0}, sells{0};
};

#endif