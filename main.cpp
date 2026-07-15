#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;


class Person
{
protected:
    string username = "admin";
    string password = "1234";

public:
    virtual bool login()
    {
        string u, p;

        cout << "\n========== LOGIN ==========\n";
        cout << "Username : ";
        cin >> u;

        cout << "Password : ";
        cin >> p;

        if (u == username && p == password)
        {
            cout << "\nLogin Successful!\n";
            return true;
        }

        cout << "\nInvalid Username or Password!\n";
        return false;
    }
};


class Expense
{
private:
    int id;
    string date;
    string category;
    string description;
    float amount;

public:
    Expense()
    {
        id = 0;
        amount = 0;
    }
    Expense(int i, string d, string c, string des, float a)
{
    id = i;
    date = d;
    category = c;
    description = des;
    amount = a;
}

    void input()
    {
        cout << "\nExpense ID : ";
        cin >> id;
        cin.ignore();

        cout << "Date (DD/MM/YYYY) : ";
        getline(cin, date);

        cout << "Category : ";
        getline(cin, category);

        cout << "Description : ";
        getline(cin, description);

        cout << "Amount : ";
        cin >> amount;
    }

    void display() const
    {
        cout << left
             << setw(8) << id
             << setw(15) << date
             << setw(18) << category
             << setw(25) << description
             << "Rs. " << amount << endl;
    }

    int getId() const
    {
        return id;
    }

    float getAmount() const
    {
        return amount;
    }

    string getCategory() const
    {
        return category;
    }

    void update()
    {
        cin.ignore();

        cout << "New Date : ";
        getline(cin, date);

        cout << "New Category : ";
        getline(cin, category);

        cout << "New Description : ";
        getline(cin, description);

        cout << "New Amount : ";
        cin >> amount;
    }

    void save(ofstream &file)
    {
        file << id << "|"
             << date << "|"
             << category << "|"
             << description << "|"
             << amount << endl;
    }
};


class ExpenseManager : public Person
{
private:
    vector<Expense> expenses;

public:
    void loadData()
{
    ifstream file("expenses.txt");

    if (!file)
        return;

    expenses.clear();

    while (!file.eof())
    {
        Expense e;

        int id;
        string date, category, description;
        float amount;
        char ch;

        if (!(file >> id))
            break;

        file >> ch; // |

        getline(file, date, '|');
        getline(file, category, '|');
        getline(file, description, '|');
        file >> amount;

        file.ignore();

        // Create expense object
        Expense temp(id, date, category, description, amount);

        expenses.push_back(temp);
    }

    file.close();
}

    void addExpense()
    {
        Expense e;
        e.input();

        expenses.push_back(e);

        cout << "\nExpense Added Successfully!\n";
    }

    void viewExpenses()
    {
        if (expenses.empty())
        {
            cout << "\nNo Expenses Found!\n";
            return;
        }

        cout << "\n-------------------------------------------------------------\n";

        cout << left
             << setw(8) << "ID"
             << setw(15) << "Date"
             << setw(18) << "Category"
             << setw(25) << "Description"
             << "Amount\n";

        cout << "-------------------------------------------------------------\n";

        for (int i = 0; i < expenses.size(); i++)
        {
            expenses[i].display();
        }
    }
            
    void searchExpense()
    {
        int id;
        bool found = false;

        cout << "\nEnter Expense ID to Search : ";
        cin >> id;

        for (int i = 0; i < expenses.size(); i++)
        {
            if (expenses[i].getId() == id)
            {
                cout << "\nExpense Found\n";
                cout << "---------------------------------------------\n";
                cout << left
                     << setw(8) << "ID"
                     << setw(15) << "Date"
                     << setw(18) << "Category"
                     << setw(25) << "Description"
                     << "Amount\n";
                cout << "---------------------------------------------\n";

                expenses[i].display();
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nExpense Not Found!\n";
    }

    
    void updateExpense()
    {
        int id;
        bool found = false;

        cout << "\nEnter Expense ID to Update : ";
        cin >> id;

        for (int i = 0; i < expenses.size(); i++)
        {
            if (expenses[i].getId() == id)
            {
                expenses[i].update();
                cout << "\nExpense Updated Successfully!\n";
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nExpense Not Found!\n";
    }

    
    void deleteExpense()
    {
        int id;
        bool found = false;

        cout << "\nEnter Expense ID to Delete : ";
        cin >> id;

        for (int i = 0; i < expenses.size(); i++)
        {
            if (expenses[i].getId() == id)
            {
                expenses.erase(expenses.begin() + i);
                cout << "\nExpense Deleted Successfully!\n";
                found = true;
                break;
            }
        }

        if (!found)
            cout << "\nExpense Not Found!\n";
    }

    
    void totalExpense()
    {
        float total = 0;

        for (int i = 0; i < expenses.size(); i++)
        {
            total += expenses[i].getAmount();
        }

        cout << "\nTotal Expense = Rs. " << total << endl;
    }

    
    void saveData()
    {
        ofstream file("expenses.txt");

        for (int i = 0; i < expenses.size(); i++)
        {
            expenses[i].save(file);
        }

        file.close();

        cout << "\nData Saved Successfully!\n";
    }

};  

int main()
{
    ExpenseManager manager;
    manager.loadData();

    if (!manager.login())
    {
        return 0;
    }

    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n      EXPENSE TRACKER SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Expense";
        cout << "\n2. View Expenses";
        cout << "\n3. Search Expense";
        cout << "\n4. Update Expense";
        cout << "\n5. Delete Expense";
        cout << "\n6. Total Expense";
        cout << "\n7. Save Data";
        cout << "\n8. Exit";
        cout << "\n------------------------------------";
        cout << "\nEnter Your Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            manager.addExpense();
            break;

        case 2:
            manager.viewExpenses();
            break;

        case 3:
            manager.searchExpense();
            break;

        case 4:
            manager.updateExpense();
            break;

        case 5:
            manager.deleteExpense();
            break;

        case 6:
            manager.totalExpense();
            break;

        case 7:
            manager.saveData();
            break;

        case 8:
            cout << "\nThank You for using Expense Tracker System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Please Try Again.\n";
        }

    } while (choice != 8);

    return 0;
}
    