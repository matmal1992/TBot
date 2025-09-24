#include "headers\BotSimulator.h"
#include "headers\Graph.h"

#include <algorithm>

SimulatedData RunSimulation(const Config& cfg)
{
    CsvData data(cfg.data_file, cfg.time_interval);
    data.TrimPricesVector(cfg.trim_start, cfg.trim_end);

    DiagnosticData diag_data = data.GetDiagnosticData();
    BotSimulator bot_simulator(diag_data.prices, cfg.short_period, cfg.long_period);
    bot_simulator.RunSimulator();

    Graph graph(diag_data, bot_simulator.GetSimulatedData());
    graph.PrintLinearGraph(graph_type::short_avg_actions);
    // graph.PrintHistogram(histogram_type::diffs);

    return bot_simulator.GetSimulatedData();
}

int main()
{
    Config cfg;
    SimulatedData sim_data = RunSimulation(cfg);

    std::cout << "Sells: " << sim_data.closes << '\n'
              << "Buys: " << sim_data.opens << '\n'
              << "Balance: " << sim_data.balance << '\n';

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