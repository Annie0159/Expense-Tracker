#pragma once
#include <vector>
#include <string>

using namespace std;

// Represents a single expense entry
class Expense {
private:
    string date;      
    string category;
    double amount;
    string description;

public:
    Expense(const string& date, const string& category, double amount, const string& desc);
    
    //getters to access private members
    string getDate() const;
    string getCategory() const;
    double getAmount() const;
    string getDescription() const;
};
