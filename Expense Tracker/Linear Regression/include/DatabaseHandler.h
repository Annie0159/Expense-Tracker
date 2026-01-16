#pragma once
#include <vector>
#include <string>
#include <memory>
#include <mysqlx/xdevapi.h>
#include "Expense.h"

using namespace std;

class DatabaseHandler {
private:
    unique_ptr<mysqlx::Session> session; // connection to MySQL
    mysqlx::Schema schema; 

public:
    DatabaseHandler(const string& user, const string& password, const string& host="localhost");

    ~DatabaseHandler();
    void insertExpense(const string& date, const string& category, double amount, const string& desc);
    vector<Expense> fetchAllExpenses();
    void deleteExpense(int id);
    double totalSpent();
    double totalByCategory(const string& category);
};
