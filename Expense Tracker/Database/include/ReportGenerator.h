#pragma once
#include "ExpenseManager.h"
#include <map>

// Generates reports based on expenses
class ReportGenerator {
public:
    static void showCategorySummary(  vector<Expense> expenses); // Summary by category
    static void showTopCategory(  vector<Expense> expenses); // Top spending category
    static void showMonthlySummary(  vector<Expense> expenses); // Monthly summary
};
