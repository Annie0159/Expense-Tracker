#include <iostream>
#include "ExpenseManager.h"

using namespace std;

int main() {
    // Initialize ExpenseManager
    ExpenseManager manager;
    int choice;
    do {
        // Display menu
        cout << "\n===== Expense Tracker =====\n";
        cout << "1. Add Expense\n";
        cout << "2. List Expenses\n";
        cout << "3. View Total\n";
        cout << "4. View Total by Category\n";
        cout << "5. Delete Expense\n";
        cout << "6. Reports\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string date, category, desc;
                double amount;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter category: ";
                cin >> category;
                cout << "Enter amount: ";
                cin >> amount;
                cin.ignore();
                cout << "Enter description: ";
                getline(cin, desc);
                manager.addExpense(date, category, amount, desc);
                break;
            }
            case 2:
                manager.listExpenses();
                break;
            case 3:
                cout << "Total spent: " << manager.totalSpent() << "\n";
                break;
            case 4: {
                string cat;
                cout << "Enter category: ";
                cin >> cat;
                cout << "Total in " << cat << ": " << manager.totalByCategory(cat) << "\n";
                break;
            }
            case 5: {
                int id;
                cout << "Enter expense ID to delete: ";
                cin >> id;
                manager.deleteExpense(id);
                break;
            }
            case 6:
                manager.generateReport();
                break;
            case 0:
                cout << "Quiting!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);
    return 0;
}
