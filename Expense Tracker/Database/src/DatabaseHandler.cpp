#include "DatabaseHandler.h"
#include "Expense.h"
#include <mysqlx/xdevapi.h>
#include <iostream>

using namespace std;
using namespace mysqlx;

DatabaseHandler::DatabaseHandler(const std::string& user, const std::string& password,
                                 const std::string& host)
    : session(std::make_unique<Session>(host, user, password)),
      schema(session->getSchema("expenses_database"))
{
    std::cout << "Connected to MySQL database successfully!\n";
}

// Destructor: Closes the database session
DatabaseHandler::~DatabaseHandler() {
    if (session) {
        session->close();
    }
}

void DatabaseHandler::insertExpense(const std::string& date,
                                    const std::string& category,
                                    double amount,
                                    const std::string& desc) {
    try {
        Table expenses = schema.getTable("expenses");  
        expenses.insert("date", "category", "amount", "description")
                .values(date, category, amount, desc)
                .execute();
        std::cout << "Expense added successfully.\n";
    } catch (const mysqlx::Error& err) {
        std::cerr << "Insert error: " << err.what() << "\n";
    }
}

std::vector<Expense> DatabaseHandler::fetchAllExpenses() {
    std::vector<Expense> list;
    try {
        Table expenses = schema.getTable("expenses");
        RowResult res = expenses
            .select("id", "CAST(date AS CHAR)", "category", "amount", "description")
            .execute();

        for (Row row : res) {
            int id = row[0].get<int>();
            std::string date = row[1].get<std::string>();
            std::string category = row[2].get<std::string>();
            double amount = row[3].get<double>();
            std::string desc = row[4].get<std::string>();
            list.emplace_back(date, category, amount, desc, id);
        }
    } catch (const mysqlx::Error& err) {
        std::cerr << "Fetch error: " << err.what() << "\n";
    }

    return list;
}

void DatabaseHandler::deleteExpense(int id) {
    try {
        Table expenses = schema.getTable("expenses");
        expenses.remove().where("id = :id").bind("id", id).execute();
        std::cout << "Expense deleted successfully.\n";
    } catch (const mysqlx::Error& err) {
        std::cerr << "Delete error: " << err.what() << "\n";
    }
}

double DatabaseHandler::totalSpent() {
    try {
        auto res = session->sql("SELECT SUM(amount) FROM expenses_database.expenses").execute();
        if (res.count() > 0) return res.fetchOne()[0].get<double>();
    } catch (const mysqlx::Error& err) {
        std::cerr << "Total error: " << err.what() << "\n";
    }
    return 0.0;
}

double DatabaseHandler::totalByCategory(const std::string& category) {
    try {
        auto res = session->sql("SELECT SUM(amount) FROM expenses_database.expenses WHERE category = ?")
                        .bind(category)
                        .execute();
        if (res.count() > 0) return res.fetchOne()[0].get<double>();
    } catch (const mysqlx::Error& err) {
        std::cerr << "Category total error: " << err.what() << "\n";
    }
    return 0.0;
}
