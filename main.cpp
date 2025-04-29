#include "headers\BotSimulator.h"

#include <algorithm>

int main()
{
    // std::vector<double> test_prices {1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9, 10, 11, 9, 10, 11, 12, 13, 14};
    // std::reverse(test_prices.begin(), test_prices.end());

    CsvData data("data/US500_prices.csv", 1);
    // CsvData data(test_prices);
    BotSimulator bot_simulator(data.GetPrices(), 2, 8);
    std::cout << "Balance: " << bot_simulator.GetBalance() << std::endl;
    std::cout << "GetShortAvg size: " << bot_simulator.GetShortAvg().size() << std::endl;

    data.PrintGraph(data.GetDiagnosticData(), bot_simulator.GetActions(), bot_simulator.GetShortAvg());

    return 0;
}
// Concentrate at the beginning on peaks. Track various indexes - dynamic ones.
// to do: printing multiple graphs. Averages. Trends...
// after closing a position, wait some time - to check
// next - more detailed diagnostics