#include "LoadCsvData.h"

#include <deque>

class BotSimulator
{
  // friend class BotSimulatorTest;

public:
  BotSimulator(const std::vector<double> &prices);

  // private:
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
  const size_t amount_of_current_records = 5;
  const double percentage_profit = 0.05;
  const double percentage_loss = 0.05;
  const double percentage_peak_profit = 0.2;
  const double percentage_peak_loss = 0.2;
  const size_t investing_value = 5000;

  double balance{0};
  size_t buys{0}, sells{0};
};