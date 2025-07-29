#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Bank
{
    string user_name;
    int bank_accNo;
    string password;
    double balance;

    bool isAccNoUnique(int accNo)
    {
        ifstream fin("account.txt");
        int acc;
        string n, pa;
        double b;
        while (fin >> acc >> ws && getline(fin, n, '|') && fin >> pa >> b)
        {
            if (acc == accNo)
                return false;
        }
        return true;
    }

    int generateUniqueAccNo()
    {
        int accNo;
        do
        {
            accNo = 1000 + rand() % 9000;
        } while (!isAccNoUnique(accNo));
        return accNo;
    }

public:
    void createAccount(string name, double deposit, string pass)
    {
        if (deposit < 0)
        {
            cout << "Initial deposit cannot be negative.\n";
            return;
        }
        int accNo = generateUniqueAccNo();
        ofstream fout("account.txt", ios::app);
        fout << accNo << " " << name << "|" << " " << pass << " " << deposit << endl;
        fout.close();
        cout << "Your account has been created successfully.\nAccount No: " << accNo << endl;
    }

    bool verifyPassword(const string &actualPass)
    {
        int attempts = 3;
        string inputPass;
        while (attempts--)
        {
            cout << "Enter password: ";
            cin >> inputPass;
            if (inputPass == actualPass)
                return true;
            cout << "Incorrect password. Attempts left: " << attempts << endl;
        }
        return false;
    }

    void depositMoney(int accNo, double deposit)
    {
        if (deposit < 0)
        {
            cout << "Amount cannot be negative.\n";
            return;
        }

        ifstream fin("account.txt");
        ofstream temp("temp.txt");
        int acc;
        string n, pa;
        double b;
        bool found = false;

        while (fin >> acc >> ws && getline(fin, n, '|') && fin >> pa >> b)
        {
            if (acc == accNo)
            {
                if (!verifyPassword(pa))
                {
                    temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
                    continue;
                }
                b += deposit;
                cout << "Amount deposited successfully.\nNew balance: " << b << endl;
                found = true;
            }
            temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
        }
        fin.close();
        temp.close();
        remove("account.txt");
        rename("temp.txt", "account.txt");

        if (!found)
            cout << "Account not found.\n";
    }

    void withDrawMoney(int accNo, double amount)
    {
        if (amount < 0)
        {
            cout << "Amount cannot be negative.\n";
            return;
        }

        ifstream fin("account.txt");
        ofstream temp("temp.txt");
        int acc;
        string n, pa;
        double b;
        bool found = false;

        while (fin >> acc >> ws && getline(fin, n, '|') && fin >> pa >> b)
        {
            if (acc == accNo)
            {
                if (!verifyPassword(pa))
                {
                    temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
                    continue;
                }

                if (b >= amount)
                {
                    b -= amount;
                    cout << "Withdrawal successful. Remaining balance: " << b << endl;
                }
                else
                {
                    cout << "Insufficient balance.\n";
                }
                found = true;
            }
            temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
        }
        fin.close();
        temp.close();
        remove("account.txt");
        rename("temp.txt", "account.txt");

        if (!found)
            cout << "Account not found.\n";
    }

    void balanceInquiry(int accNo)
    {
        ifstream fin("account.txt");
        int acc;
        string n, pa;
        double b;
        bool found = false;

        while (fin >> acc >> ws && getline(fin, n, '|') && fin >> pa >> b)
        {
            if (acc == accNo)
            {
                if (!verifyPassword(pa))
                {
                    fin.close();
                    return;
                }
                cout << "Your current balance: " << b << endl;
                found = true;
                break;
            }
        }
        fin.close();
        if (!found)
            cout << "Account not found.\n";
    }

    void displayAccount(int accNo)
    {
        ifstream fin("account.txt");
        int acc;
        string n, pa;
        double b;
        bool found = false;

        while (fin >> acc >> ws && getline(fin, n, '|') && fin >> pa >> b)
        {
            if (acc == accNo)
            {
                if (!verifyPassword(pa))
                {
                    fin.close();
                    return;
                }
                cout << "Username: " << n << "\nAccount No: " << acc << "\nBalance: " << b << endl;
                found = true;
                break;
            }
        }
        fin.close();
        if (!found)
            cout << "Account not found.\n";
    }

    void deleteAccount(int accNo)
    {
        ifstream fin("account.txt");
        ofstream temp("temp.txt");
        int acc;
        string n, pa;
        double b;
        bool found = false;

        while (fin >> acc >> ws && getline(fin, n, '|') && fin >> pa >> b)
        {
            if (acc == accNo)
            {
                if (!verifyPassword(pa))
                {
                    temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
                    continue;
                }

                char confirm;
                cout << "Are you sure you want to delete this account? (Y/N): ";
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y')
                {
                    cout << "Account deleted.\n";
                    found = true;
                    continue; // Skip writing this account
                }
            }
            temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
        }
        fin.close();
        temp.close();
        remove("account.txt");
        rename("temp.txt", "account.txt");

        if (!found)
            cout << "Account not found or not deleted.\n";
    }

    void modifyAccount(int accNo)
    {
        ifstream fin("account.txt");
        ofstream temp("temp.txt");
        int acc;
        string n, pa;
        double b;
        bool found = false;

        while (fin >> acc >> ws && getline(fin, n, '|') && fin >> pa >> b)
        {
            if (acc == accNo)
            {
                if (!verifyPassword(pa))
                {
                    temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
                    continue;
                }
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, n);
                cout << "Enter new password: ";
                cin >> pa;
                found = true;
            }
            temp << acc << " " << n << "|" << " " << pa << " " << b << endl;
        }
        fin.close();
        temp.close();
        remove("account.txt");
        rename("temp.txt", "account.txt");

        if (found)
            cout << "Account modified successfully.\n";
        else
            cout << "Account not found.\n";
    }
};

int main()
{
    srand(time(0)); // Seed random only once
    Bank b;
    int choice, accNo;
    string userName, pass;
    double amount;

    while (true)
    {
        cout << "\n------ Bank Menu ------\n"
             << "1. Create Account\n"
             << "2. Deposit Money\n"
             << "3. Withdraw Money\n"
             << "4. Balance Inquiry\n"
             << "5. Modify Account\n"
             << "6. Delete Account\n"
             << "7. Display Account\n"
             << "8. Exit\n"
             << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Set your user name: ";
            getline(cin, userName);
            cout << "Set your password: ";
            cin >> pass;
            cout << "Enter initial deposit: ";
            cin >> amount;
            b.createAccount(userName, amount, pass);
            break;
        case 2:
            cout << "Enter account number and amount: ";
            cin >> accNo >> amount;
            b.depositMoney(accNo, amount);
            break;
        case 3:
            cout << "Enter account number and amount: ";
            cin >> accNo >> amount;
            b.withDrawMoney(accNo, amount);
            break;
        case 4:
            cout << "Enter account number: ";
            cin >> accNo;
            b.balanceInquiry(accNo);
            break;
        case 5:
            cout << "Enter account number: ";
            cin >> accNo;
            b.modifyAccount(accNo);
            break;
        case 6:
            cout << "Enter account number: ";
            cin >> accNo;
            b.deleteAccount(accNo);
            break;
        case 7:
            cout << "Enter account number: ";
            cin >> accNo;
            b.displayAccount(accNo);
            break;
        case 8:
            cout << "Thank you for using our banking system!\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
