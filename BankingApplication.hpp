#ifndef _BANKINGAPPLICATION_HPP
#define _BANKINGAPPLICATION_HPP
#include <iostream>
class BankingApplication
{
public:
    BankingApplication ();
    bool addClient ();
    void menu ();
};
//-----------------------------------
class client
{
private:
    std::string name;
    std::string address;
    std::string phoneNumber;
public:
    client ();
    client (std::string n , std::string a , std::string pN);
    std::string getName ();
    std::string getAddress ();
    std::string getPhoneNumber ();
};
//-----------------------------------
class BankAccount
{
protected:
    std::string accountID;
    double balance;
public:
    BankAccount ();
    BankAccount (double b);
    std::string getAccountID ();
    double getBalance ();
    void setAccountID (std::string AID);
    virtual void withdraw (double amount);
    virtual void deposit (double amount);
    virtual std::string getType();
};
//-----------------------------------
class SavingsBankAccount : public BankAccount
{
private:
    double minimumBalance;
public:
    SavingsBankAccount ();
    SavingsBankAccount (double startingB , double minB);
    double getMinimumBalance ();
    void withdraw (double amount);
    void deposit (double amount);
    std::string getType();
};
#endif // BANKINGAPPLICATION_HPP_INCLUDED
