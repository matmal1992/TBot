#include "headers\BotSimulator.h"

int main()
{
    CsvData data("US500_prices.csv");
    LoadedData prices = data.LoadDataFromFile();
    BotSimulator bot_simulator(prices.prices);
    DiagnosticData diagnostic_data = data.GetDiagnosticData(prices.prices);

    bot_simulator.Iterate();

    std::vector<bool> opens = bot_simulator.GetActions().opens;

    std::cout << "Average Price: " << diagnostic_data.avg_price << std::endl;

    std::cout << "Average difference: " << diagnostic_data.avg_difference << std::endl;
    std::cout << "Biggest difference: " << diagnostic_data.biggest_difference << std::endl;
    std::cout << "Biggest difference index: " << diagnostic_data.biggest_difference_index << std::endl;

    std::cout << "Average deviation: " << diagnostic_data.avg_deviation << std::endl;
    std::cout << "Biggest deviation: " << diagnostic_data.biggest_deviation << std::endl;
    std::cout << "Biggest deviation index: " << diagnostic_data.biggest_difference_index << std::endl;

    data.PrintGraph(prices, opens);

    return 0;
}
