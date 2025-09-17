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
    double balance {0};
    int opens {0}, closes {0};
};

class BotSimulator
{
public:
    BotSimulator(const std::vector<double>& prices, const int short_period = 0, const int long_period = 0);

    SimulatedData GetSimulatedData();

private:
    void Iterate();
    void AddRecord(int record_index);
    void MakeDecision();
    void OpenPosition();
    void ClosePosition();
    double CalculateAverage(size_t period);

    SimulatedData data_;
    std::vector<double> prices_;
    std::deque<double> current_records;
    size_t initial_deposit = 5000;
    bool position_opened {false};
    double open_value {0}, spread {0};
    size_t short_period_, long_period_;
};

#endif