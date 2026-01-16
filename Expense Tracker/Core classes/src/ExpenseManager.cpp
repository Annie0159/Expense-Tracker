#include "ExpenseManager.h"
#include "ReportGenerator.h"
#include "ExpenseStorage.h"
#include <iostream>
#include <iomanip>

using namespace std;

ExpenseManager::ExpenseManager()
{
    expenses = ExpenseStorage::loadExpenses();
}

ExpenseManager::~ExpenseManager()
{
    ExpenseStorage::saveExpenses(expenses);
}

// Add a new expense
void ExpenseManager::addExpense(const std::string& date, const std::string& category,
                                double amount, const std::string& description) {
    Expense exp(date, category, amount, description);
    expenses.push_back(exp);
}


// List all expenses
void ExpenseManager::listExpenses() {
    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }
    // Header
    cout << left << setw(5) << "ID"
              << setw(12) << "Date"
              << setw(15) << "Category"
              << setw(10) << "Amount"
              << "Description\n";
    cout << "------------------------------------------------------------\n";

    int id = 1;
    for (auto e : expenses) {
        cout << setw(5) << id++
                  << setw(12) << e.getDate()
                  << setw(15) << e.getCategory()
                  << setw(10) << e.getAmount()
                  << e.getDescription() << "\n";
    }
}

// Calculate total expenses
double ExpenseManager::totalSpent() {
    double total = 0.0;
    for (const auto& e : expenses)
        total += e.getAmount();
    return total;
}

// Total by category
double ExpenseManager::totalByCategory(const string& category) {
    double total = 0.0;
    for (const auto& e : expenses)
        if (e.getCategory() == category)
            total += e.getAmount();
    return total;
}

// Delete expense by index
void ExpenseManager::deleteExpense(int index) {
    if (index < 1 || index > (int)expenses.size()) {
        cout << "Invalid ID.\n";
        return;
    }
    expenses.erase(expenses.begin() + (index - 1));
    cout << "Expense deleted.\n";
}


void ExpenseManager::generateReport()
{
    listExpenses();
    ReportGenerator::showCategorySummary(expenses);
    ReportGenerator::showTopCategory(expenses);
    ReportGenerator::showMonthlySummary(expenses);
}

