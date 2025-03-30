#include "LoadCsvData.h"

class BotSimulator {
public:
  BotSimulator(const std::vector<double> &prices);

private:
  void AddRecord();
  void CheckTrend();
  void Buy();
  void Sell();
  bool IsConstantLoss();
  bool IsConstantRise();

  std::vector<double> prices_;
  std::vector<double> current_records;
  const size_t amount_of_current_records = 5;
  const size_t percentage_profit = 20;
  const size_t percentage_loss = 20;
  const size_t investing_value = 5000;

  double balance{0};
  size_t buys{0}, sells{0};
};