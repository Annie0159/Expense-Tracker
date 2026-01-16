#pragma once
#include <vector>
#include <string>

using namespace std;

// Represents a single expense entry
class Expense {
private:
    int id;             
    string date;      // format: YYYY-MM-DD
    string category;
    double amount;
    string description;

public:
    Expense(const string& date, const string& category, double amount, const string& desc,int id=-1);
    
    //getters to access private members
    int getId() const;
    string getDate() const;
    string getCategory() const;
    double getAmount() const;
    string getDescription() const;

    // Setter for ID 
    void setId(int newId);
};
