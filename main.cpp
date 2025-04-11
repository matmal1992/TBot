#include "headers\BotSimulator.h"

int main()
{
    std::vector<double> test_prices {1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 7, 8, 9, 10, 9, 10, 11, 12, 13};
    std::vector<std::string> test_dates;
    for (int i {0}; i < test_prices.size(); ++i) { test_dates.push_back(std::to_string(i)); }

    CsvData data("US500_prices.csv");
    // LoadedData prices = data.LoadDataFromFile();
    LoadedData prices {test_prices, test_dates};
    // BotSimulator bot_simulator(prices.prices);
    BotSimulator bot_simulator(test_prices);
    // DiagnosticData diagnostic_data = data.GetDiagnosticData(prices.prices);
    DiagnosticData diagnostic_data = data.GetDiagnosticData(test_prices);

    bot_simulator.Iterate();

    std::vector<bool> opens = bot_simulator.GetActions().opens;
    std::vector<bool> closes = bot_simulator.GetActions().closes;

    data.PrintGraph(prices, diagnostic_data, opens, closes); // to do: rescale y axis 10x smaller

    return 0;
}
