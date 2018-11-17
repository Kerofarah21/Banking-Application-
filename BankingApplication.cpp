#include "BankingApplication.hpp"
#include <iostream>
using namespace std;
BankingApplication::BankingApplication ()
{

}
void BankingApplication::menu ()
{
    cout << "Welcome to FCI Banking Application" << endl;
    int n=0;
    client *owner;
    owner=new client[5];
    BankAccount *acc[5];
    while (true)
    {
        cout << "What do you want to do\n1- Create a new account\n2- List clients and accounts" << endl;
        cout << "3- Withdraw money\n4- Deposit money\n0- Exit the Application" << endl;
        char choose;
        cin >> choose;
        if (choose=='1')
        {
            string ID="FCI-00";
            ID+=char(n+49);
            string name,address,phone;
            cout << "Enter client name =====> ";
            cin.ignore();
            getline(cin,name);
            cout << "Enter client address =====> ";
            getline(cin,address);
            cout << "Enter client phone =====> ";
            cin >> phone;
            owner[n]=client(name,address,phone);
            while (true)
            {
                cout << "What type of account do you like? (1)Basic or (2)Saving =====> ";
                char choice;
                cin >> choice;
                if (choice=='1')
                {
                    cout << "Please enter the starting balance: ";
                    double B;
                    cin >> B;
                    acc[n]=new BankAccount(B);
                    acc[n]->setAccountID(ID);
                    break;
                }
                else if (choice=='2')
                {
                    cout << "Please enter the starting balance: ";
                    double B;
                    cin >> B;
                    cout << "Please enter the minimum balance: ";
                    double MB;
                    cin >> MB;
                    while (B<MB)
                    {
                        cout << "Starting balance must be greater than or equal to the minimum balance" << endl;
                        cout << "Please enter the starting balance: ";
                        cin >> B;
                        cout << "Please enter the minimum balance: ";
                        cin >> MB;
                    }
                    acc[n]=new SavingsBankAccount(B,MB);
                    acc[n]->setAccountID(ID);
                    break;
                }
                else
                    cout << "Choose only 1 or 2" << endl;
            }
            cout << "Account created with ID " << acc[n]->getAccountID() << " and starting balance " << acc[n]->getBalance() << " L.E" << endl;
            n++;
        }
        else if (choose=='2' && n>0)
        {
            for (int i=0 ; i<n ; i++)
            {
                cout << "-------------------- " << owner[i].getName() << " --------------------" << endl;
                cout << "Address: " << owner[i].getAddress() << "  Phone: " << owner[i].getPhoneNumber() << endl;
                cout << "Account ID: " << acc[i]->getAccountID() << "  (" << acc[i]->getType() << ")" << endl;
                cout << "Balance: " << acc[i]->getBalance() <<endl<<endl;
            }
        }
        else if (choose=='3' && n>0)
        {
            cout << "Please enter Account ID (e.g., FCI-003): ";
            string accID;
            cin >> accID;
            for (int i=0 ; i<n ; i++)
            {
                if (accID==acc[i]->getAccountID())
                {
                    cout << "Account ID: " << acc[i]->getAccountID() << endl;
                    cout << "Account type: " << acc[i]->getType() << endl;
                    cout << "Balance: " << acc[i]->getBalance() <<endl;
                    cout << "Enter the amount to withdraw =====> ";
                    int amount;
                    cin >> amount;
                    acc[i]->withdraw(amount);
                    break;
                }
                else if (i==n-1 && n>0)
                {
                    cout << "Not valid Account ID, choose from 1 to " << n << " Accounts: ";
                    cin >> accID;
                    i=-1;
                }
            }
        }
        else if (choose=='4' && n>0)
        {
            cout << "Please enter Account ID (e.g., FCI-003): ";
            string accID;
            cin >> accID;
            for (int i=0 ; i<n ; i++)
            {
                if (accID==acc[i]->getAccountID())
                {
                    cout << "Account ID: " << acc[i]->getAccountID() << endl;
                    cout << "Account type: " << acc[i]->getType() << endl;
                    cout << "Balance: " << acc[i]->getBalance() <<endl;
                    cout << "Enter the amount to deposit =====> ";
                    int amount;
                    cin >> amount;
                    acc[i]->deposit(amount);
                    break;
                }
                else if (i==n-1)
                {
                    cout << "Not valid Account ID, choose from 1 to " << n << " Accounts";
                    cin >> accID;
                    i=-1;
                }
            }
        }
        else if ((choose=='2' || choose=='3' || choose=='4') && n==0)
            cout << "There is no Accounts yet, you must enter some first" << endl;
        else if (choose=='0')
            break;
        else
            cout << "Please choose from 1 to 4 or 0 only" << endl;
    }
}
//---------client class-----------
client::client ()
{

}
client::client (std::string n , std::string a , std::string pN)
{
    name=n;
    address=a;
    phoneNumber=pN;
}
std::string client::getName ()
{
    return name;
}
std::string client::getAddress ()
{
    return address;
}
std::string client::getPhoneNumber ()
{
    return phoneNumber;
}
//---------BankAccount class-----------
BankAccount::BankAccount ()
{
    balance=0;
}
BankAccount::BankAccount (double b)
{
    balance=b;
}
std::string BankAccount::getAccountID ()
{
    return accountID;
}
void BankAccount::setAccountID (std::string AID)
{
    accountID=AID;
}
double BankAccount::getBalance ()
{
    return balance;
}
void BankAccount::withdraw (double amount)
{
    while (balance < amount)
    {
        cout << "Balance isn't sufficient for this withdraw" << endl;
        cout << "Enter the amount you want to withdraw: ";
        cin >> amount;
    }
    balance -=amount;
    cout << "Thank you\nAccount ID: " << accountID <<"\nBalance: " << balance << endl;
}
void BankAccount::deposit (double amount)
{
    balance+=amount;
    cout << "Thank you\nAccount ID: " << accountID <<"\nBalance: " << balance << endl;
}
std::string BankAccount::getType()
{
    return "Basic";
}

//----------SavingsBankAccount class--------

SavingsBankAccount::SavingsBankAccount ()
{
    minimumBalance=1000;
}
SavingsBankAccount::SavingsBankAccount (double startingB, double minB)
{
    balance=startingB;
    minimumBalance=minB;
}
double SavingsBankAccount::getMinimumBalance ()
{
    return minimumBalance;
}
void SavingsBankAccount::withdraw (double amount)
{
    while (minimumBalance > (balance-amount))
    {
        cout << "Unavailable withdraw, you can't drop the balance below the minimum balance" << endl;
        cout << "Enter the amount you want to withdraw: ";
        cin >> amount;
    }
    balance -=amount;
    cout << "Thank you\nAccount ID: " << accountID <<"\nBalance: " << balance << endl;
}
void SavingsBankAccount::deposit (double amount)
{
    while (amount <100)
    {
        cout << "You should deposit at least 100 L.E in every time" << endl;
        cout << "Enter the amount you want to withdraw: ";
        cin >> amount;
    }
    balance+=amount;
    cout << "Thank you\nAccount ID: " << accountID <<"\nBalance: " << balance << endl;
}
std::string SavingsBankAccount::getType()
{
    return "Saving";
}
