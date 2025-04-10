#include "headers\BotSimulator.h"

int main()
{
    std::vector<double> test_prices {1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 7, 8, 9, 10, 9, 10, 11, 12, 13};
    std::vector<std::string> test_dates {"1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9", "10",
                                         "11", "12", "13", "14", "15", "16", "17", "18", "19"};
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

    std::cout << "Average Price: " << diagnostic_data.avg_price << std::endl;

    std::cout << "Average difference: " << diagnostic_data.avg_difference << std::endl;
    std::cout << "Biggest difference: " << diagnostic_data.biggest_difference << std::endl;
    std::cout << "Biggest difference index: " << diagnostic_data.biggest_difference_index << std::endl;

    std::cout << "Average deviation: " << diagnostic_data.avg_deviation << std::endl;
    std::cout << "Biggest deviation: " << diagnostic_data.biggest_deviation << std::endl;
    std::cout << "Biggest deviation index: " << diagnostic_data.biggest_difference_index << std::endl;

    data.PrintGraph(prices, opens, closes); // to do: rescale y axis 10x smaller

    return 0;
}
