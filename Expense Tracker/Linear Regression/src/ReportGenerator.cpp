#include "ReportGenerator.h"
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

// Display summary of expenses by category
void ReportGenerator::showCategorySummary( vector<Expense> expenses) {
    if (expenses.empty()) {
        cout << "No expenses available for summary.\n";
        return;
    }

    map<string, double> totals;
    for (const auto& e : expenses)
        totals[e.getCategory()] += e.getAmount();

    cout << "\n--- Category Summary ---\n";
    for (const auto& [category, total] : totals)
        cout << setw(15) << category << ": " << total << "\n";
}

// Display the category with the highest total expense
void ReportGenerator::showTopCategory( vector<Expense> expenses) {
    if (expenses.empty()) {
        cout << "No expenses recorded.\n";
        return;
    }

    map<string, double> totals;
    for (const auto& e : expenses)
        totals[e.getCategory()] += e.getAmount();

    string topCategory;
    double maxTotal = 0.0;
    for (const auto& [category, total] : totals) {
        if (total > maxTotal) {
            maxTotal = total;
            topCategory = category;
        }
    }

    cout << "\nTop spending category: " << topCategory
              << " (" << maxTotal << ")\n";
}

// Display monthly summary of expenses
void ReportGenerator::showMonthlySummary(vector<Expense> expenses) {
    if (expenses.empty()) {
        cout << "No expenses found.\n";
        return;
    }

    // Map month (YYYY-MM) → total amount
    map<string, double> monthlyTotals;

    for (const auto& exp : expenses) {
        string date = exp.getDate(); 
        if (date.size() >= 7) {
            string month = date.substr(0, 7); 
            monthlyTotals[month] += exp.getAmount();
        }
    }

    // Print summary
    cout << "\n===== Monthly Spending Summary =====\n";
    cout << left << setw(15) << "Month" << right << setw(10) << "Total\n";
    cout << "---------------------------------\n";

    for (const auto& [month, total] : monthlyTotals) {
        cout << left << setw(15) << month << right << setw(10) << fixed << setprecision(2) << total << "\n";
    }
}

void ReportGenerator::predictNextMonth(vector<Expense> expenses) {
        if (expenses.empty()) {
            cout << "No expenses found.\n";
            return;
        }

        // Map month → total
        map<string, double> monthlyTotals;
        for (const auto& exp : expenses) {
            string month = exp.getDate().substr(0, 7);
            monthlyTotals[month] += exp.getAmount();
        }

        // Write to CSV for ML
        ofstream out("data/monthly_totals.csv");
        out << "month,total\n";
        for (const auto& [month, total] : monthlyTotals)
            out << month << "," << total << "\n";
        out.close();

        // Call Python script
        int ret = system("python3 src/predict.py data/monthly_totals.csv output/prediction.txt");
        if (ret != 0) {
            cout << "Prediction script failed.\n";
            return;
        }

        // Read back prediction
        ifstream in("output/prediction.txt");
        string prediction;
        getline(in, prediction);
        in.close();

        cout << "\nPredicted next month's spending: $" << prediction << "\n";
    }