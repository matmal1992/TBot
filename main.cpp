#include "headers\BotSimulator.h"

int main()
{
    std::vector<double> test_prices {1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9, 10, 11, 9, 10, 11, 12, 13, 14};
    std::vector<std::string> test_dates;
    for (int i {0}; i < test_prices.size(); ++i) { test_dates.push_back(std::to_string(i)); }

    CsvData data("US500_prices.csv");
    BotSimulator bot_simulator(test_prices);
    DiagnosticData diagnostic_data = data.GetDiagnosticData(test_prices);

    // data.PrintGraph(diagnostic_data, bot_simulator.GetOpens(), bot_simulator.GetCloses());
    data.PrintGraph(diagnostic_data, bot_simulator.GetOpens(), bot_simulator.GetCloses());

    return 0;
}
