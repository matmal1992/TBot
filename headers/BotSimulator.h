#ifndef BOT_SIMULATOR_H
#define BOT_SIMULATOR_H

#include "LoadCsvData.h"
#include "Patterns.h"
#include <deque>
#include <numeric>

class BotSimulator
{
public:
    BotSimulator(const std::vector<double>& prices, const int short_period = 0, const int long_period = 0);

    std::vector<std::pair<bool, bool>> GetActions();
    std::vector<double> GetLongAvg();
    std::vector<double> GetShortAvg();
    double GetBalance();

private:
    void Iterate();
    void AddRecord(int record_index);
    double CalculateAverage(size_t period);
    void ActWithLongAndShortStrategy();
    void ActWithSingleAvgStrategy(size_t price_index);
    void ActWithSimpleStrategy(size_t prizc_index);
    void PrintVector(const std::deque<double>& vec);

    // first -> open_pos | second -> close_pos
    std::vector<std::pair<bool, bool>> actions;
    std::vector<double> prices_, short_averages_, long_averages_;
    std::deque<double> current_records;
    size_t initial_deposit = 5000;

    bool position_opened {false};
    double open_value {0}, balance {0}, spread {1};
    size_t short_period_, long_period_;
};

#endif