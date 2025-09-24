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
    std::vector<action> actions;
    double balance {0};
    size_t opens {0}, closes {0};
};

class BotSimulator
{
public:
    BotSimulator(const std::vector<double>& prices, const size_t short_period = 0, const size_t long_period = 0);

    const SimulatedData& GetSimulatedData() const;
    void RunSimulator();

private:
    void AddRecord(int record_index);
    void MakeDecision();
    void OpenPosition();
    void ClosePosition();
    double CalculateAverage(size_t period) const;
    bool ShouldOpen() const;
    bool ShouldClose() const;

    SimulatedData data_;
    std::vector<double> prices_;
    std::deque<double> current_records_;
    bool position_opened {false};
    double open_value {0};
    size_t short_period_, long_period_;
    const double spread_ {0};
};

#endif