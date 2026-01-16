#pragma once
#include "ExpenseManager.h"
#include <string>

// Utility class to save and load expenses from file
class ExpenseStorage {
public:
    static void saveExpenses(vector<Expense>& expenses);
    static vector<Expense> loadExpenses();

private:
    static const std::string file_path; // path to expense CSV file
};
