#include <deque>
#include <iostream>
#include <string>
#include <vector>

double perc_profit = 1.2;
std::vector<double> prices_{1.1, 1.0, 3.6, 3.7, 5.0};
std::deque<double> current_records{1.1};
std::vector<bool> opens;
std::vector<bool> closes;

void PrintCurrentRecords() {
    std::cout << "current_records: ";
    for (size_t i = 0; i < current_records.size(); i++) {
        std::cout << current_records[i] << " | ";
    }
    std::cout << std::endl;
}

void AddRecord(int record_index) {
    if (current_records.size() < 3) {
        current_records.push_back(prices_.at(record_index));
    } else {
        current_records.pop_front();
        current_records.push_back(prices_.at(record_index));
    }
    PrintCurrentRecords();
}

bool IsSuddenRise() {
    for (size_t i = 1; i < current_records.size(); i++) {
        if (current_records.at(current_records.size() - 1) >
            current_records.at(current_records.size() - 2) * perc_profit) {
            return true;
        }
    }
    return false;
}

void Iterate() {
    int amount_of_opens{0};

    for (size_t i{1}; i < prices_.size(); ++i) {
        AddRecord(i);
        if (/*IsConstantRise() or */ IsSuddenRise()) {
            opens.push_back(true);
            closes.push_back(false);
            amount_of_opens++;
        } else {
            opens.push_back(false);
            closes.push_back(false);
        }
        // else if (/*IsConstantFall() or */ IsSuddenFall())
        // {
        //   actions.opens.at(i) = false;
        //   actions.closes.at(i) = true;
        // }

        // if (prices_[i] > prices_[i - 1] * perc_profit) {
        //     amount_of_opens++;
        // }
    }
    std::cout << "Size of opens after iteration: " << opens.size();
              << std::endl;
}

int main() {
    Iterate();
    return 0;
}
