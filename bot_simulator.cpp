#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  std::ifstream file("US500_prices.csv");
  if (!file) {
    std::cerr << "Error: Unable to open file.\n";
    return 1;
  }

  std::vector<double> prices;
  std::string line;

  // Skip the first line (header)
  std::getline(file, line);

  // Read prices from CSV
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string date, priceStr;

    // Extract date and price
    std::getline(ss, date, ',');     // Read first column (date)
    std::getline(ss, priceStr, ','); // Read second column (price)

    try {
      double price = std::stod(priceStr);
      prices.push_back(price);
    } catch (...) {
      std::cerr << "Skipping invalid data: " << priceStr << "\n";
    }
  }

  file.close();

  // Compute the average
  if (prices.empty()) {
    std::cerr << "No valid price data found.\n";
    return 1;
  }

  double sum = 0;
  for (double price : prices) {
    sum += price;
  }

  double average = sum / prices.size();

  // Display the result
  std::cout << "Average Price: " << std::fixed << std::setprecision(2)
            << average << "\n";

  return 0;
}
