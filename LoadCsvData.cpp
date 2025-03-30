#include "LoadCsvData.h"

CsvData::CsvData(const std::string &path) : path_(path) { ; }

std::vector<double> CsvData::LoadPrices() {

  std::vector<double> prices;

  std::ifstream file(path_);
  if (!file) {
    std::cerr << "Error: Unable to open file.\n";
    return prices;
  }

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
  return prices;
}

void CsvData::PrintGraph() {
  std::ifstream file("US500_prices.csv");
  if (!file) {
    std::cerr << "Error: Unable to open file.\n";
  }

  std::vector<std::string> time;
  std::vector<double> price;
  std::string line, timestamp, priceStr;

  // Skip the first line (header)
  std::getline(file, line);

  // Read data
  while (std::getline(file, line)) {
    size_t commaPos = line.find(',');
    if (commaPos != std::string::npos) {
      timestamp = line.substr(0, commaPos);
      priceStr = line.substr(commaPos + 1);

      try {
        double priceValue = std::stod(priceStr);
        time.push_back(timestamp);
        price.push_back(priceValue);
      } catch (...) {
        continue;
      }
    }
  }
  file.close();

  // Write data to a temporary file for gnuplot
  std::ofstream tempFile("plot_data.txt");
  for (size_t i = 0; i < time.size(); i++) {
    tempFile << i << " " << price[i]
             << "\n"; // Use index instead of time for x-axis
  }
  tempFile.close();

  // Generate gnuplot command
  std::string command = "gnuplot -e \"plot 'plot_data.txt' using 1:2 with "
                        "lines title 'US500 Price'; pause -1\"";
  system(command.c_str());
}

double CsvData::GetAvgValue(std::vector<double> data) {
  if (data.empty()) {
    std::cerr << "No valid price data found.\n";
    return 0;
  }

  double sum = 0;
  for (double price : data) {
    sum += price;
  }

  double average = sum / data.size();
  return average;
}