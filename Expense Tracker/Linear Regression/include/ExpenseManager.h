#pragma once

#include <vector>
#include <string>
#include "Expense.h"
#include "ReportGenerator.h"
#include "DatabaseHandler.h"

using namespace std;

// Manages a collection of expenses
class ExpenseManager {
private:
    vector<Expense> expenses;
    DatabaseHandler db; // Database handler instance

public:
    ExpenseManager(); // Constructor to initialize DatabaseHandler from config file

    void addExpense(const std::string& date, const std::string& category,double amount, const std::string& description); // Add a new expense
    void listExpenses(); // List all expenses
    double totalSpent();// Calculate total expenses
    double totalByCategory(const string& category); // Total by category
    void deleteExpense(int index); // Delete expense by index
    void generateReport(); // Generate various reports
};
