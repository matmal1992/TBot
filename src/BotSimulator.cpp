#include "..\headers\BotSimulator.h"

BotSimulator::BotSimulator(const std::vector<double> &prices)
    : prices_(prices) {}

void BotSimulator::AddRecord(int record_index)
{
  if (current_records.size() < 5)
  {
    current_records.push_back(prices_.at(record_index));
  }
  else
  {
    current_records.pop_back();
    current_records.push_front(prices_.at(record_index));
  }
}

bool BotSimulator::IsConstantFall()
{
  for (size_t i = 1; i < current_records.size(); ++i)
  {
    if (current_records[i] < current_records[i - 1])
    {
      return false;
    }
  }
  return true;
}

bool BotSimulator::IsConstantRise()
{
  for (size_t i = 1; i < current_records.size(); ++i)
  {
    if (current_records[i] > current_records[i - 1])
    {
      return false;
    }
  }
  return true;
}

bool BotSimulator::IsSuddenRise()
{
  for (size_t i = 1; i < current_records.size(); ++i)
  {
    if (current_records[i] > current_records[i - 1] * percentage_peak_profit)
    {
      return true;
    }
  }
  return false;
}

bool BotSimulator::IsSuddenFall()
{
  for (size_t i = 1; i < current_records.size(); ++i)
  {
    if (current_records[i] > current_records[i - 1] * percentage_peak_profit)
    {
      return true;
    }
  }
  return false;
}

void BotSimulator::CheckTrend() {}
void BotSimulator::Buy() {}
void BotSimulator::Sell() {}
