#ifndef BEHAVIOURS_H
#define BEHAVIOURS_H

#include <cstddef>
#include <deque>

const double percentage_profit = 0.05;
const double percentage_loss = 0.05;
const double percentage_peak_profit = 1.9;
const double percentage_peak_loss = 1.9;

bool IsConstantFall(const std::deque<double>& current_records);
bool IsConstantRise(const std::deque<double>& current_records);
bool IsSuddenFall(const std::deque<double>& current_records);
bool IsSuddenRise(const std::deque<double>& current_records);
bool SingleRise(const std::deque<double>& current_records);
bool SingleFall(const std::deque<double>& current_records);
bool TwoRisesInRow(const std::deque<double>& current_records);
bool TwoFallsInRow(const std::deque<double>& current_records);

#endif