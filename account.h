#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "lib.h"

struct Account {
    string username;
    string password;
};

// Helper Function
vector<Account> loadAccounts();
vector<string> loadWeakPasswords();
bool isValidAccount(vector<Account> accounts, vector<string> weakPasswords, Account acc);
void saveAccount(Account newAccount);

// Registration
void registerAccount(vector<Account> accounts, vector<string> weakPasswords);
void multipleRegistrations(vector<Account> accounts, vector<string> weakPasswords);

// Login
bool checkLogIn(vector<Account> accounts, Account account) ;
void login(vector<Account> accounts);

// Change Password
void changePassword(vector<Account> accounts, vector<string> weakPasswords, Account &account) ;

#endif // ACCOUNT_H