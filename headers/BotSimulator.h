#ifndef BOT_SIMULATOR_H
#define BOT_SIMULATOR_H

#include "LoadCsvData.h"
#include <deque>

class BotSimulator
{
public:
    BotSimulator(const std::vector<double>& prices);
    std::vector<std::pair<bool, bool>> GetActions();

private:
    bool IsConstantFall();
    bool IsConstantRise();
    bool IsSuddenFall();
    bool IsSuddenRise();
    bool SingleRiseDetected();
    bool SingleFallDetected();

    void Iterate();
    void AddRecord(int record_index);
    // void ActWithMoerComplicatedStrategy();
    void ActWithSimpleStrategy();
    void PrintVector(const std::deque<double>& vec);

    std::vector<double> prices_;
    std::deque<double> current_records;
    size_t amount_of_current_records = 5;
    double percentage_profit = 0.05;
    double percentage_loss = 0.05;
    double percentage_peak_profit = 1.9;
    double percentage_peak_loss = 1.9;
    size_t investing_value = 5000;

    bool position_opened {false};
    double balance {0};

    // first -> open_pos | second -> close_pos
    std::vector<std::pair<bool, bool>> actions;
};

#endif