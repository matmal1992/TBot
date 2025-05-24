#ifndef BOT_SIMULATOR_H
#define BOT_SIMULATOR_H

#include "LoadCsvData.h"
#include "Patterns.h"
#include <deque>
#include <numeric>

struct SimulatedData
{
    std::vector<double> short_averages;
    std::vector<double> long_averages;
    std::vector<std::pair<bool, bool>> actions; // first -> open_pos | second -> close_pos
};

class BotSimulator
{
public:
    BotSimulator(const std::vector<double>& prices, const int short_period = 0, const int long_period = 0);

    SimulatedData GetSimulatedData();
    double GetBalance();

private:
    void Iterate();
    void AddRecord(int record_index);
    double CalculateAverage(size_t period);
    void ActWithLongAndShortStrategy();
    void ActWithSingleAvgStrategy(size_t price_index);
    void ActWithSimpleStrategy(size_t price_index);
    void ShortAvgTrend(size_t price_index);
    void PrintVector(const std::deque<double>& vec);
    void ShortAvgTrend(size_t price_index, size_t dec_in_row, size_t inc_in_row);

    SimulatedData data_;
    std::vector<double> prices_;
    std::deque<double> current_records;
    size_t initial_deposit = 5000;
    bool position_opened {false};
    double open_value {0}, balance {0}, spread {0.5};
    size_t short_period_, long_period_;
};

#endif