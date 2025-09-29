#ifndef ATM_SYSTEM_H
#define ATM_SYSTEM_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

struct AccountNode {
    int accountNumber;
    std::string accountName;
    std::string birthday;
    std::string contactNumber;
    float balance;
    int pinCode;
    AccountNode* next;
};

class ATMSystem {
private:
    AccountNode* head;
    AccountNode* tail;
    int size;

public:
    // Constructor & Destructor
    ATMSystem();
    ~ATMSystem();

    // ADT List Operations
    bool isEmpty() const;
    int getSize() const;
    void insertAccount(AccountNode account);
    bool deleteAccount(int accountNumber);
    AccountNode* searchAccount(int accountNumber) const;
    AccountNode* searchAccountByPin(int pinCode) const;
    void displayAllAccounts() const;
    void clearList();

    // Utility Functions
    int generateAccountNumber();
    int generatePIN();
    bool validateInitialDeposit(float amount) const;

    // ATM Modules
    void registrationModule();
    void transactionModule();
    void displayMainMenu();
    void runATM();

    // Transaction Operations
    void balanceInquiry(AccountNode* account);
    void withdraw(AccountNode* account);
    void deposit(AccountNode* account);
    void fundTransfer(AccountNode* fromAccount);
    void changePIN(AccountNode* account);
};

#endif
