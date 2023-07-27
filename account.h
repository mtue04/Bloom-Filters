#ifndef ACCOUNT_H
#define ACCOUNT_H


#include "lib.h"
#include "bloom-filter.cpp"

struct Account {
    string username;
    string password;
};

// Helper Function
void loadAccounts(vector<Account> &accounts);
void loadWeakPasswords();
bool isValidAccount(vector<Account> accounts, Account acc);
void saveAccount(Account newAccount);
void writeFail(string username, string password);

// Registration
void registerAccount(vector<Account> accounts);
void multipleRegistrations(vector<Account> accounts);

// Login
bool checkLogIn(vector<Account> accounts, Account account) ;
bool login(vector<Account> accounts, Account &acc);

// Change Password
void changePassword(vector<Account> accounts, Account &account) ;


#endif // ACCOUNT_H