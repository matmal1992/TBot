#include "headers\BotSimulator.h"

#include <algorithm>

int main()
{
    std::vector<double> test_prices {1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9, 10, 11, 9, 10, 11, 12, 13, 14};
    std::reverse(test_prices.begin(), test_prices.end());

    // CsvData data("US500_prices.csv");
    CsvData data(test_prices);
    // BotSimulator bot_simulator(test_prices);
    BotSimulator bot_simulator(data.GetPrices());
    std::cout << "Balance: " << bot_simulator.GetBalance() << std::endl;

    data.PrintGraph(data.GetDiagnosticData(), bot_simulator.GetActions());

    return 0;
}
