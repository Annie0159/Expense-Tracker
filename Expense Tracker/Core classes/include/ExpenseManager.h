#pragma once

#include <vector>
#include <string>
#include "Expense.h"

using namespace std;

// Manages a collection of expenses
class ExpenseManager {
private:
    vector<Expense> expenses;

public:
    ExpenseManager();
    ~ExpenseManager();
    
    void addExpense(const std::string& date, const std::string& category,double amount, const std::string& description); // Add a new expense
    void listExpenses(); // List all expenses
    double totalSpent();// Calculate total expenses
    double totalByCategory(const string& category); // Total by category
    void deleteExpense(int index); // Delete expense by index
    void generateReport(); // for ReportGenerator
};
