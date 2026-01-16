#include "ExpenseManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

static void readConfig(string& user, string& password, string& host) {
    ifstream config("config.txt");
    if (!config.is_open()) {
        cerr << "Error: Could not open configfile.txt" << endl;
        exit(EXIT_FAILURE);
    }

    unordered_map<string, string> settings;
    string line;
    while (getline(config, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t pos = line.find('=');
        if (pos == string::npos) continue;
        settings[line.substr(0, pos)] = line.substr(pos + 1);
    }

    user = settings["user"];
    password = settings["password"];
    host = settings["host"];
}

ExpenseManager::ExpenseManager()
    : db([]
          {
              string user, password, host;
              readConfig(user, password, host);
              return DatabaseHandler(user, password, host);
          }()) // immediately invoked lambda to build db
{
    cout << "ExpenseManager initialized using configfile.txt\n";
}

// Add a new expense
void ExpenseManager::addExpense(const string& date, const string& category,
                                double amount, const string& description) {
    db.insertExpense(date, category, amount, description);
}

// List all expenses
void ExpenseManager::listExpenses() {
    if(expenses.size() < 350)
    {
        expenses.clear();
        auto rows = db.fetchAllExpenses();
        for (const auto& e : rows) 
            expenses.push_back(e); 

        if (expenses.empty()) {
            cout << "No expenses recorded.\n";
            return;
        }
    }
    cout << left << setw(5) << "ID"
              << setw(12) << "Date"
              << setw(15) << "Category"
              << setw(10) << "Amount"
              << "Description\n";
    cout << "------------------------------------------------------------\n";
    for (auto e : expenses) {
        cout << setw(5) << e.getId()
                  << setw(12) << e.getDate()
                  << setw(15) << e.getCategory()
                  << setw(10) << e.getAmount()
                  << e.getDescription() << "\n";
    }
}

// Calculate total expenses
double ExpenseManager::totalSpent() {
    return db.totalSpent();
}

// Total by category
double ExpenseManager::totalByCategory(const string& category)  {
    return db.totalByCategory(category);
}

// Delete expense by index
void ExpenseManager::deleteExpense(int index) {
    db.deleteExpense(index);
}


void ExpenseManager::generateReport()
{
    listExpenses();
    ReportGenerator::showCategorySummary(expenses);
    ReportGenerator::showTopCategory(expenses);
    ReportGenerator::showMonthlySummary(expenses);
}