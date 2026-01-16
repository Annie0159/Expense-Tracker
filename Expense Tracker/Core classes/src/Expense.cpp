#include "Expense.h"

using namespace std;

// Constructor to initialize an expense
Expense::Expense(const string& d,
                 const string& c,
                 double a,
                 const string& desc)
    : date(d), category(c), amount(a), description(desc) {}

// Getters
string Expense::getDate() const { 
    return date; 
}
string Expense::getCategory() const {
    return category; 
}
double Expense::getAmount() const { 
    return amount; 
}
string Expense::getDescription() const { 
    return description; 
}
