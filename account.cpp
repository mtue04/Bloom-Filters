#include "account.h"

void loadWeakPasswords() {
    ifstream ifs("WeakPass.txt");
    if (!ifs.is_open())
        return;

    string pass;
    while (getline(ifs, pass)) {
        addWeakPasswordToBloomFilter(pass);
    }
    ifs.close();
}

bool isValidPassword(Account acc) {
    // Check constraints for password and return true/false accordingly
    if (acc.password.size() <= 10 || acc.password.size() >= 20) {
        cout << "Length of " << acc.username << "'s password must be in the range of (10, 20). . ." << endl;
        return false;
    }

    if (acc.password.find(' ') != -1) {
        cout << acc.username << "'s password must not contain SPACE inside . . ." << endl;
        return false;
    }
    
    if (acc.password.find(acc.username) != -1) {
        cout << acc.username << "'s password must not contain username . . ." << endl;
        return false;
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
        cout << acc.username << "'s password must have at least one uppercase character, one lowercase character, one number and one special character . . ." << endl;
        return false;
    }

    if (isWeakPassword(acc.password)) {
        ifstream ifs("WeakPass.txt");
        string weakPassword;
        while (getline(ifs, weakPassword)) 
            if (acc.password == weakPassword) {
                cout << acc.username << "'s password is too weak . . ." << endl;
                return false;
            }
            ifs.close();
    }

    return true;
}

bool isValidAccount(vector<Account> accounts, Account acc) {
    // Check constraints for username and return true/false accordingly
    if (acc.username.size() <= 5 || acc.username.size() >= 10) {
        cout << "Length of " << acc.username << "'s username must be in the range of (5, 10) . . ." << endl;
        return false;
    }

    if (acc.username.find(' ') != -1) {
        cout << acc.username << "'s username must not contain SPACE inside . . ." << endl;
        return false;
    }

    if (isUserExists(acc.username)) {
        cout << acc.username << "'s username is registered . . ." << endl;
        return false;
    }
    
    if (!isValidPassword(acc))
        return false;

    return true;
}

void writeFail(string username, string password) {
    // Note the sign-up information fail due to constraints violation to Fail.txt file
    ofstream ofs("Fail.txt", ios::app);

    if (!ofs.is_open()) {
        cout << "Error: Unable to save accounts to Fail.txt" << endl;
        return;
    }

    ofs << username << " " << password << endl;

    ofs.close();
}

void registerAccount(vector<Account> &accounts) {
    // Register a single account if it meets all constraints and add it to the accounts vector
    // Input account 
    Account newAccount;
    cout << "USERNAME: ";
    cin >> newAccount.username;
    cout << "PASSWORD: ";
    cin >> newAccount.password;

    // Check new account
    if (isValidAccount(accounts, newAccount)) {
        accounts.push_back(newAccount);
        addUsernameToBloomFilter(newAccount.username);
        cout << "Account " << newAccount.username << " registered successfully!" << endl;
    }
}

void multipleRegistrations(vector<Account> &accounts) {
    // Register multiple accounts provided in accounts data and add them to the accounts vector
    // Input account 
    vector<Account> listNewAccounts;
    bool haveFail = false;

    ifstream ifs("SignUp.txt");
    if (!ifs.is_open()) {
        cout << "Error: Unable to save accounts to SignUp.txt" << endl;
        return;
    }
    
    string line;
    while(getline(ifs, line)) {
        Account acc;
        stringstream ss(line);
        getline(ss, acc.username, ' ');
        getline(ss, acc.password, ' ');
        if (isValidAccount(accounts, acc)) {
            accounts.push_back(acc);
            addUsernameToBloomFilter(acc.username);
            cout << "Account " << acc.username << " registered successfully!" << endl;
        } else {
            writeFail(acc.username, acc.password);
            haveFail = true;
        }
    }
    
    if (haveFail) {
        cout << "Accounts that cannot be created due to constraints violation moved to output file \"Fail.txt\" . . ." << endl;
    }
}

bool checkLogIn(vector<Account> accounts, Account account) {
    if (isUserExists(account.username)) {
        for (int i = 0; i < accounts.size(); i++) 
            if (accounts[i].username == account.username && accounts[i].password == account.password)
                return true;
        cout << "Wrong password . . . " << endl;
    } else {
        cout << "Invalid username . . . " << endl;
    }
    return false;
}

bool login(vector<Account> accounts, Account &acc) {
    Account account;
    cout << "USERNAME: ";
    cin >> account.username;
    cout << "PASSWORD: ";
    cin >> account.password;
    if (checkLogIn(accounts, account)) {
        acc.username = account.username;
        acc.password = account.password;
        cout << "Login successfully . . ." << endl;
        return true;
    }
    return false;
}

void changePassword(vector<Account> &accounts, Account &account) {
    string newPassword;
    string newPasswordCheck;
    cout << "NEW PASSWORD: ";
    cin >> newPassword;
    cout << "CONFIRM: ";
    cin >> newPasswordCheck;
    if (newPassword == newPasswordCheck) {
        Account acc;
        acc.username = account.username;
        acc.password = newPassword;
        if (isValidPassword(acc)) {
            account.password = newPassword;
            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].username == account.username) {
                    accounts[i].password = newPassword;
                }
            }
            cout << account.username << "'s password was changed successfully!" << endl;
        } else {
            cout << account.username << "'s password do not change . . ." << endl;
        }
    } else {
        cout << "Confirmation is fail . . ." << endl;
    }
}