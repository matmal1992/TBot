#include "headers\BotSimulator.h"
#include "headers\Graph.h"

#include <algorithm>

int main()
{
    // std::vector<double> test_prices {1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9, 10, 11, 9, 10, 11, 12, 13, 14};
    // std::reverse(test_prices.begin(), test_prices.end());

    const int short_period {2};
    const int long_period {8};
    const int time_interval {1};

    CsvData data("testing_data/US500_prices.csv", time_interval);
    // CsvData data(test_prices);
    BotSimulator bot_simulator(data.GetPrices(), short_period, long_period);
    std::cout << "Balance: " << bot_simulator.GetBalance() << std::endl;
    std::cout << "GetShortAvg size: " << bot_simulator.GetShortAvg().size() << std::endl;

    DiagnosticData diag_data = data.GetDiagnosticData();
    std::vector<std::pair<bool, bool>> actions = bot_simulator.GetActions();
    std::vector<double> short_avg = bot_simulator.GetShortAvg();
    std::vector<double> prices = data.GetPrices();

    // Graph graph(data.GetDiagnosticData(), bot_simulator.GetActions(), bot_simulator.GetShortAvg(), data.GetPrices());
    Graph graph(diag_data, actions, short_avg, prices);
    graph.PrintActions();
    // data.PrintGraph(data.GetDiagnosticData(), bot_simulator.GetActions(), bot_simulator.GetShortAvg());

    return 0;
}
// Concentrate at the beginning on peaks. Track various indexes - dynamic ones.
// to do: printing multiple graphs. Averages. Trends...
// after closing a position, wait some time - to check
// next - more detailed diagnostics