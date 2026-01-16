#include "Expense.h"

using namespace std;

// Constructor to initialize an expense
Expense::Expense(const string& date, const string& category, double amount, const string& desc,int id)
    : id(id), date(date), category(category), amount(amount), description(desc) {}

// Getters
int Expense::getId() const {
    return id;
}
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

// Setter for ID
void Expense::setId(int newId) {
    id = newId;
}
