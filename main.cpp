#include "headers\BotSimulator.h"
#include "headers\Graph.h"

#include <algorithm>

int main()
{
    const int short_period {10};
    const int long_period {24};
    const int time_interval {1};

    CsvData data("testing_data/US500_prices.csv", time_interval);
    DiagnosticData diag_data = data.GetDiagnosticData();

    BotSimulator bot_simulator(diag_data.prices, short_period, long_period);
    SimulatedData sim_data = bot_simulator.GetSimulatedData();

    std::cout << "Sells: " << sim_data.closes << std::endl;
    std::cout << "Buys: " << sim_data.opens << std::endl;
    std::cout << "Balance: " << sim_data.balance << std::endl;

    Graph graph(diag_data, sim_data);
    graph.PrintLinearGraph(graph_type::short_avg_actions);
    // graph.PrintHistogram(histogram_type::diffs);

    return 0;
}
// Concentrate at the beginning on peaks. Track various indexes - dynamic ones.
// after closing a position, wait some time - to check
// track increases and decreases of averages
// track avg devs and diffs of long and short avgs. Also max values.
// try to add 3 or 4 averages, and track their diffs and devs.
// peaks - buy when short crosses, sell when long crosses. (ptyhon script: short - 5, long - 15). Try with diff values.
// przebicie z góry do dołu, ostry peak - kup. Podobnie zaobserwować drugą stronę. I na różnych średnich.
// ostry peak w górę - później poziomo - sprzedaj.