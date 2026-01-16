#include "ExpenseStorage.h"
#include "Expense.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem> 

using namespace std;

const string ExpenseStorage::file_path = "data/expenses.csv";

void ExpenseStorage::saveExpenses( vector<Expense>& expenses) {
    namespace fs = filesystem;

    // Ensure the directory exists
    try {
        fs::create_directories(fs::path(file_path).parent_path());
    } catch (const exception& e) {
        cerr << "Error creating directory: " << e.what() << "\n";
        return;
    }

    // open or create the file for writing
    ofstream file(file_path, ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Could not open or create " << file_path << " for writing.\n";
        return;
    }

    // Write CSV header
    file << "Date,Category,Amount,Description\n";

    for (const auto& expense : expenses) {
        file << expense.getDate() << ","
             << expense.getCategory() << ","
             << expense.getAmount() << ","
             << expense.getDescription() << "\n";
    }

    file.close();
    cout << "Expenses saved to " << file_path << "\n";
}

vector<Expense> ExpenseStorage::loadExpenses() {
    vector<Expense> expenses;
    namespace fs = filesystem;

    // Ensure the directory exists
    try {
        fs::create_directories(fs::path(file_path).parent_path());
    } catch (const exception& e) {
        cerr << "Error creating directory: " << e.what() << "\n";
        return expenses;
    }

    // If the file doesn't exist yet
    if (!fs::exists(file_path)) {
        cout<< "No existing expense file found.\n";
        return expenses;
    }

    // Open the file for reading
    ifstream file(file_path);
    if (!file.is_open()) {
        cerr << "Error: Could not open " << file_path << " for reading.\n";
        return expenses;
    }

    string line;
    getline(file, line); // skip header line

    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string date, category, amount_str, description;

        getline(ss, date, ',');
        getline(ss, category, ',');
        getline(ss, amount_str, ',');
        getline(ss, description);

        try {
            double amount = stod(amount_str);
            Expense exp(date, category, amount, description);
            expenses.push_back(exp);
            ++count;
        } catch (...) {
            cerr << "Skipping invalid line in expenses.csv\n";
        }
    }

    file.close();
    cout << "Loaded " << count << " expenses from " << file_path << "\n";
    return expenses;
}
