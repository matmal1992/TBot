#include "headers\BotSimulator.h"
#include "headers\Graph.h"

#include <algorithm>

int main()
{
    // std::vector<double> test_prices {1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9, 10, 11, 9, 10, 11, 12, 13, 14};
    // std::reverse(test_prices.begin(), test_prices.end());

    const int short_period {30};
    const int long_period {24};
    const int time_interval {1};

    CsvData data("testing_data/US500_prices.csv", time_interval);
    DiagnosticData diag_data = data.GetDiagnosticData();

    // CsvData data(test_prices);
    BotSimulator bot_simulator(diag_data.prices, short_period, long_period);
    SimulatedData sim_data = bot_simulator.GetSimulatedData();
    std::cout << "Balance: " << bot_simulator.GetBalance() << std::endl;

    Graph graph(diag_data, sim_data);
    graph.PrintLinearGraph(graph_type::both_avg);
    // graph.PrintHistogram(histogram_type::diffs);

    return 0;
}
// Concentrate at the beginning on peaks. Track various indexes - dynamic ones.
// after closing a position, wait some time - to check
// track increases and decreases of averages
// track avg devs and diffs of long and short avgs. Also max values.
// try to add 3 or 4 averages, and track their diffs and devs.
// peaks - buy when short crosses, sell when long crosses. (ptyhon script: short - 5, long - 15). Try with diff values.