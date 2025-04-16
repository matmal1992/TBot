#ifndef BOT_SIMULATOR_H
#define BOT_SIMULATOR_H

#include "LoadCsvData.h"
#include <deque>
#include <numeric>

class BotSimulator
{
public:
    BotSimulator(const std::vector<double>& prices, const int short_period = 0, const int long_period = 0);
    std::vector<std::pair<bool, bool>> GetActions();
    double GetBalance();

private:
    bool IsConstantFall();
    bool IsConstantRise();
    bool IsSuddenFall();
    bool IsSuddenRise();
    bool SingleRise();
    bool SingleFall();
    bool TwoRisesInRow();
    bool TwoFallsInRow();

    void Iterate();
    void AddRecord(int record_index);
    double CalculateAverage(size_t period);
    void ActWithLongAndShortStrategy();
    void ActWithSimpleStrategy(size_t prizc_index);
    void PrintVector(const std::deque<double>& vec);

    std::vector<double> prices_;
    std::deque<double> current_records;
    double percentage_profit = 0.05;
    double percentage_loss = 0.05;
    double percentage_peak_profit = 1.9;
    double percentage_peak_loss = 1.9;
    size_t investing_value = 5000;

    bool position_opened {false};
    double open_value {0}, balance {0};
    size_t short_period_, long_period_;

    // first -> open_pos | second -> close_pos
    std::vector<std::pair<bool, bool>> actions;
};

#endif