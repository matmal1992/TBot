#include "headers\BotSimulator.h"

int main()
{
    std::vector<double> test_prices {1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9, 10, 11, 9, 10, 11, 12, 13, 14};

    // CsvData data("US500_prices.csv");
    CsvData data(test_prices);
    BotSimulator bot_simulator(test_prices);

    data.PrintGraph(data.GetDiagnosticData(), bot_simulator.GetActions());

    return 0;
}
