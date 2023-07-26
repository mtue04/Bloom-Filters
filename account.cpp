#include "account.h"

vector<Account> loadAccounts() {
    // Load existing accounts from SignUp.txt file and add them to the accounts vector
    // Each line of the file contains 1 account with username and password separated by a space
    ifstream ifs("SignUp.txt");
    vector<Account> accounts;
    string line;

    if (!ifs.is_open())
        return accounts;
    
    while (!ifs.eof()) {
        Account acc;
        getline(ifs, line);
        stringstream ss(line);
        getline(ss, acc.username, ' ');
        getline(ss, acc.password, ' ');
        accounts.push_back(acc);
    }
    ifs.close();

    return accounts;
}

vector<string> loadWeakPasswords() {
    // Load weak passwords from WeakPass.txt file and add them to the weakPasswords vector
    ifstream ifs("WeakPass.txt");
    vector<string> passwords;

    if (!ifs.is_open())
        return passwords;
    
    while (!ifs.eof()) {
        string pass;
        getline(ifs, pass);
        passwords.push_back(pass);
    }
    ifs.close();

    return passwords;
}

bool isValidAccount(vector<Account> accounts, vector<string> weakPasswords, Account acc) {
    // Check constraints for username and return true/false accordingly
    if (acc.username.size() <= 5 || acc.username.size() >= 10) {
        return false;
    }

    if (acc.username.find(' ') != -1) {
        return false;
    }

    for (int i = 0; i < accounts.size(); i++)
        if (accounts[i].username == acc.username) {
            return false;
        }
    
    // Check constraints for password and return true/false accordingly
    if (acc.password.size() <= 10 || acc.password.size() >= 20) {
        return false;
    }

    if (acc.password.find(' ') != -1) {
        return false;
    }
    
    if (acc.password == acc.username) {
    }

    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasNumber = false;
    bool hasSpecialChar = false;

    for (char ch : acc.password) {
        if (isupper(ch))
            hasUpperCase = true;
        else if (islower(ch))
            hasLowerCase = true;
        else if (isdigit(ch))
            hasNumber = true;
        else if (!isalnum(ch))
            hasSpecialChar = true;
    }

    if (!(hasUpperCase && hasLowerCase && hasNumber && hasSpecialChar)) {
        return false;
    }

    for (int i = 0; i < weakPasswords.size(); i++)
        if (weakPasswords[i] == acc.password) {
            return false;
        }

    // OK > True
    return true;
}

void saveAccount(Account newAccount) {
    // Save the account information back to the SignUp.txt file
    ofstream ofs("SignUp.txt", ios::app);

    if (!ofs.is_open()) {
        cout << "Error: Unable to save accounts to SignUp.txt" << endl;
        return;
    }

    ofs << newAccount.username << " " << newAccount.password << endl;

    ofs.close();
}

void registerAccount(vector<Account> accounts, vector<string> weakPasswords) {
    // Register a single account if it meets all constraints and add it to the accounts vector
    // Input account 
    Account newAccount;
    cout << "USERNAME: ";
    cin >> newAccount.username;
    cout << "PASSWORD: ";
    cin >> newAccount.password;

    // Check new account
    if (isValidAccount(accounts, weakPasswords, newAccount)) {
        accounts.push_back(newAccount);
        saveAccount(newAccount);
        cout << "Account registered successfully!" << endl;
    } else {
        cout << "Invalid username or password. Account registration failed . . ." << endl;
    }
}

void multipleRegistrations(vector<Account> accounts, vector<string> weakPasswords) {
    // Register multiple accounts provided in accountsData and add them to the accounts vector
    // Input account 
    vector<Account> listNewAccounts;
    char check;
    bool stop = false;

    while(!stop) {
        Account newAccount;
        cout << "USERNAME: ";
        cin >> newAccount.username;
        cout << "PASSWORD: ";
        cin >> newAccount.password;
        listNewAccounts.push_back(newAccount);

        cout << "Press 1 to continue generating another account . . .";
        cin >> check;
        if (check == '1')
            stop = true;
    }

    // Check new accounts
    for (int i = 0; i < listNewAccounts.size(); i++) {
        if (isValidAccount(accounts, weakPasswords, listNewAccounts[i])) {
            accounts.push_back(listNewAccounts[i]);
            saveAccount(listNewAccounts[i]);
            cout << "Account for username " << listNewAccounts[i].username << " registered successfully!" << endl;
        } else {
            cout << "Invalid username or password for account: " << listNewAccounts[i].username << ". Account registration failed . . ." << endl;
        }
    }
}

bool checkLogIn(vector<Account> accounts, Account account) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].username == account.username && accounts[i].password == account.password)
            return true;

        if (accounts[i].username == account.username && accounts[i].password != account.password) {
            do {
                cout << "Wrong password. Try again . . . " << endl;
                getline(cin, account.password, '\n');
            } while (accounts[i].password != account.password);
            return true;
        }
    }
    cout << "Invalid username . . . " << endl;
    return false;
}

void login(vector<Account> accounts) {
    Account account;
    do {
        cout << "USERNAME: ";
        getline(cin, account.username, '\n');
        cout << "PASSWORD: ";
        getline(cin, account.password, '\n');
    } while (!checkLogIn(accounts, account));
}

void changePassword(vector<Account> accounts, vector<string> weakPasswords, Account &account) {
    string newPassword;
    string newPasswordCheck;
    cout << "NEW PASSWORD: ";
    getline(cin, newPassword, '\n');
    cout << "CONFIRM: ";
    getline(cin, newPasswordCheck, '\n');
    if (newPassword == newPasswordCheck) {
        Account acc;
        acc.username = account.username;
        acc.password = newPassword;
        if (isValidAccount(accounts, weakPasswords, acc)) {
            account.password = newPassword;
            ofstream ofs("SignUp.txt");
            if (!ofs.is_open())
                return;
            
            for (int i = 0; i < accounts.size(); i++) {
                ofs << accounts[i].username << " " << accounts[i].password << endl;
            }

            ofs.close();
        }
    }
}