#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Account Node Structure
struct AccountNode {
    int accountNumber;
    string accountName;
    string birthday;
    string contactNumber;
    float balance;
    int pinCode;
    AccountNode* next;
};

// ATM System Class
class ATMSystem {
private:
    AccountNode* head;
    AccountNode* tail;
    int size;

public:
    // Constructor
    ATMSystem() : head(nullptr), tail(nullptr), size(0) {
        srand(time(0)); // Seed for random numbers
    }

    // Destructor
    ~ATMSystem() {
        clearList();
    }

    // Check if list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Get size of list
    int getSize() const {
        return size;
    }

    // Insert new account
    void insertAccount(AccountNode account) {
        AccountNode* newNode = new AccountNode;
        newNode->accountNumber = account.accountNumber;
        newNode->accountName = account.accountName;
        newNode->birthday = account.birthday;
        newNode->contactNumber = account.contactNumber;
        newNode->balance = account.balance;
        newNode->pinCode = account.pinCode;
        newNode->next = nullptr;

        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        size++;
        cout << "Account " << account.accountNumber << " successfully registered!\n";
    }

    // Delete account by account number
    bool deleteAccount(int accountNumber) {
        if (isEmpty()) return false;

        AccountNode* current = head;
        AccountNode* previous = nullptr;

        while (current != nullptr && current->accountNumber != accountNumber) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) return false;

        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }

        if (current == tail) {
            tail = previous;
        }

        delete current;
        size--;
        return true;
    }

    // Search account by account number
    AccountNode* searchAccount(int accountNumber) const {
        AccountNode* current = head;
        while (current != nullptr) {
            if (current->accountNumber == accountNumber) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Search account by PIN code
    AccountNode* searchAccountByPin(int pinCode) const {
        AccountNode* current = head;
        while (current != nullptr) {
            if (current->pinCode == pinCode) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Display all accounts
    void displayAllAccounts() const {
        if (isEmpty()) {
            cout << "No accounts in the system.\n";
            return;
        }

        AccountNode* current = head;
        cout << "\n=== ALL REGISTERED ACCOUNTS ===" << endl;
        cout << "Total accounts: " << size << endl << endl;

        while (current != nullptr) {
            cout << "Account Number: " << current->accountNumber << endl;
            cout << "Account Name: " << current->accountName << endl;
            cout << "Birthday: " << current->birthday << endl;
            cout << "Contact: " << current->contactNumber << endl;
            cout << fixed << setprecision(2) << "Balance: Php " << current->balance << endl;
            cout << "PIN Code: " << current->pinCode << endl;
            cout << "---------------------------" << endl;
            current = current->next;
        }
    }

    // Clear the entire list
    void clearList() {
        AccountNode* current = head;
        while (current != nullptr) {
            AccountNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Generate random account number
    int generateAccountNumber() {
        return 10000 + rand() % 90000; // 5-digit number
    }

    // Generate random PIN
    int generatePIN() {
        return 1000 + rand() % 9000; // 4-digit number
    }

    // Validate initial deposit
    bool validateInitialDeposit(float amount) const {
        return amount >= 5000.0;
    }

    // ==================== ATM MODULES ====================

    // Registration Module
    void registrationModule() {
        cout << "\n=== ACCOUNT REGISTRATION ===" << endl;

        AccountNode newAccount;
        newAccount.accountNumber = generateAccountNumber();
        newAccount.pinCode = generatePIN();

        cout << "Enter Account Name: ";
        cin.ignore();
        getline(cin, newAccount.accountName);

        cout << "Enter Birthday: ";
        getline(cin, newAccount.birthday);

        cout << "Enter Contact Number: ";
        getline(cin, newAccount.contactNumber);

        cout << "Enter Initial Deposit (Minimum Php 5000): ";
        cin >> newAccount.balance;

        if (!validateInitialDeposit(newAccount.balance)) {
            cout << "Error: Initial deposit must be at least Php 5000.\n";
            return;
        }

        insertAccount(newAccount);

        cout << "\n=== REGISTRATION SUCCESSFUL ===" << endl;
        cout << "Account Number: " << newAccount.accountNumber << endl;
        cout << "Your PIN: " << newAccount.pinCode << endl;
        cout << "Please remember your PIN for transactions.\n";
    }

    // Balance Inquiry
    void balanceInquiry(AccountNode* account) {
        cout << "\n=== BALANCE INQUIRY ===" << endl;
        cout << "Account: " << account->accountName << endl;
        cout << "Account Number: " << account->accountNumber << endl;
        cout << fixed << setprecision(2) << "Current Balance: Php " << account->balance << endl;
    }

    // Withdraw
    void withdraw(AccountNode* account) {
        cout << "\n=== WITHDRAW ===" << endl;
        float amount;
        cout << "Enter amount to withdraw: Php ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Error: Amount must be positive.\n";
            return;
        }

        if (amount > account->balance) {
            cout << "Error: Insufficient funds.\n";
            return;
        }

        account->balance -= amount;
        cout << "Withdrawal successful!\n";
        cout << fixed << setprecision(2) << "New Balance: Php " << account->balance << endl;
    }

    // Deposit
    void deposit(AccountNode* account) {
        cout << "\n=== DEPOSIT ===" << endl;
        float amount;
        cout << "Enter amount to deposit: Php ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Error: Amount must be positive.\n";
            return;
        }

        account->balance += amount;
        cout << "Deposit successful!\n";
        cout << fixed << setprecision(2) << "New Balance: Php " << account->balance << endl;
    }

    // Fund Transfer
    void fundTransfer(AccountNode* fromAccount) {
        cout << "\n=== FUND TRANSFER ===" << endl;
        int targetAccount;
        float amount;

        cout << "Enter target account number: ";
        cin >> targetAccount;
        cout << "Enter amount to transfer: Php ";
        cin >> amount;

        if (amount <= 0) {
            cout << "Error: Amount must be positive.\n";
            return;
        }

        if (amount > fromAccount->balance) {
            cout << "Error: Insufficient funds.\n";
            return;
        }

        AccountNode* toAccount = searchAccount(targetAccount);
        if (toAccount == nullptr) {
            cout << "Error: Target account not found.\n";
            return;
        }

        fromAccount->balance -= amount;
        toAccount->balance += amount;

        cout << "Transfer successful!\n";
        cout << fixed << setprecision(2) << "Transferred: Php " << amount << " to account " << targetAccount << endl;
        cout << "Your new balance: Php " << fromAccount->balance << endl;
    }

    // Change PIN
    void changePIN(AccountNode* account) {
        cout << "\n=== CHANGE PIN ===" << endl;
        int newPIN;
        cout << "Enter new 4-digit PIN: ";
        cin >> newPIN;

        if (newPIN < 1000 || newPIN > 9999) {
            cout << "Error: PIN must be 4 digits.\n";
            return;
        }

        account->pinCode = newPIN;
        cout << "PIN successfully changed!\n";
    }

    // Transaction Module
    void transactionModule() {
        cout << "\n=== TRANSACTION MODULE ===" << endl;
        int pin;
        cout << "Enter your PIN: ";
        cin >> pin;

        AccountNode* account = searchAccountByPin(pin);
        if (account == nullptr) {
            cout << "Error: Invalid PIN!\n";
            return;
        }

        int choice;
        do {
            cout << "\n=== TRANSACTION MENU ===" << endl;
            cout << "1. Balance Inquiry" << endl;
            cout << "2. Withdraw" << endl;
            cout << "3. Deposit" << endl;
            cout << "4. Fund Transfer" << endl;
            cout << "5. Change PIN" << endl;
            cout << "6. Return to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: balanceInquiry(account); break;
                case 2: withdraw(account); break;
                case 3: deposit(account); break;
                case 4: fundTransfer(account); break;
                case 5: changePIN(account); break;
                case 6: cout << "Returning to main menu...\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 6);
    }

    // Display Main Menu
    void displayMainMenu() {
        cout << "\n=== ATM SIMULATION SYSTEM ===" << endl;
        cout << "1. Account Registration" << endl;
        cout << "2. Transaction Module" << endl;
        cout << "3. Display All Accounts" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
    }

    // Run ATM System
    void runATM() {
        int choice;

        // Add some sample accounts for testing
        AccountNode sample1 = {12345, "Juan Dela Cruz", "1990-05-15", "09171234567", 10000.0, 1234, nullptr};
        AccountNode sample2 = {67890, "Maria Santos", "1985-08-20", "09179876543", 15000.0, 5678, nullptr};
        insertAccount(sample1);
        insertAccount(sample2);

        cout << "=== WELCOME TO ATM SYSTEM ===" << endl;
        cout << "Sample accounts created for testing:" << endl;
        cout << "Account 1: PIN 1234" << endl;
        cout << "Account 2: PIN 5678" << endl;

        do {
            displayMainMenu();
            cin >> choice;

            switch (choice) {
                case 1: registrationModule(); break;
                case 2: transactionModule(); break;
                case 3: displayAllAccounts(); break;
                case 4: cout << "Thank you for using ATM System!\n"; break;
                default: cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }
};

// Main Function
int main() {
    ATMSystem atm;
    atm.runATM();
    return 0;
}
