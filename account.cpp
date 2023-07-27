#include "account.h"

void loadAccounts(vector<Account> &accounts) {
    ifstream ifs("SignUp.txt");
    if (!ifs.is_open())
        return;

    string line;
    while (getline(ifs, line)) {
        Account acc;
        stringstream ss(line);
        getline(ss, acc.username, ' ');
        getline(ss, acc.password, ' ');
        addUsernameToBloomFilter(acc.username);
        accounts.push_back(acc);
    }
    ifs.close();
}

void loadWeakPasswords() {
    ifstream ifs("WeakPass.txt");
    if (!ifs.is_open())
        return;

    string pass;
    while (getline(ifs, pass, '\n')) {
        if (!isWeakPassword(pass))
            addWeakPasswordToBloomFilter(pass);
    }
    ifs.close();
}

bool isValidPassword(Account acc) {
    // Check constraints for password and return true/false accordingly
    if (acc.password.size() <= 10 || acc.password.size() >= 20) {
        cout << "Length of password must be in the range of (10, 20). . ." << endl;
        return false;
    }

    if (acc.password.find(' ') != -1) {
        cout << "Password must not contain SPACE inside . . ." << endl;
        return false;
    }
    
    if (acc.password == acc.username) {
        cout << "Password must not contain username . . ." << endl;
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
        cout << "Password must have at least one uppercase character, one lowercase character, one number and one special character . . ." << endl;
        return false;
    }

    if (isWeakPassword(acc.password)) {
        cout << "Your password is too weak . . ." << endl;
        return false;
    }

    return true;
}

bool isValidAccount(vector<Account> accounts, Account acc) {
    // Check constraints for username and return true/false accordingly
    if (acc.username.size() <= 5 || acc.username.size() >= 10) {
        cout << "Length of username must be in the range of (5, 10) . . ." << endl;
        return false;
    }

    if (acc.username.find(' ') != -1) {
        cout << "Username must not contain SPACE inside . . ." << endl;
        return false;
    }

    if (isUserExists(acc.username)) {
        cout << "Your username is registered . . ." << endl;
        return false;
    }
    
    if (!isValidPassword(acc))
        return false;

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

void writeFail(string username, string password) {
    // Note the sign-up information fail due to constraints violation to Fail.txt file
    ofstream ofs("Fail.txt", ios::app);

    if (!ofs.is_open()) {
        cout << "Error: Unable to save accounts to SignUp.txt" << endl;
        return;
    }

    ofs << username << " " << password << endl;

    ofs.close();
}

void registerAccount(vector<Account> accounts) {
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
        saveAccount(newAccount);
        addUsernameToBloomFilter(newAccount.username);
        cout << "Account registered successfully!" << endl;
    } else {
        writeFail(newAccount.username, newAccount.password);
    }
}

void multipleRegistrations(vector<Account> accounts) {
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

        cout << "Press 1 to stop generating multiple accounts . . ." << endl;
        cin >> check;
        if (check == '1')
            stop = true;
    }

    // Check new accounts
    for (int i = 0; i < listNewAccounts.size(); i++) {
        if (isValidAccount(accounts, listNewAccounts[i])) {
            accounts.push_back(listNewAccounts[i]);
            saveAccount(listNewAccounts[i]);
            cout << "Account for username " << listNewAccounts[i].username << " registered successfully!" << endl;
        } else {
            writeFail(listNewAccounts[i].username, listNewAccounts[i].password);
        }
    }
}

bool checkLogIn(vector<Account> accounts, Account account) {
    if (isUserExists(account.username)) {
        for (int i = 0; i < accounts.size(); i++) 
            if (accounts[i].username == accounts[i].username && accounts[i].password == account.password)
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
        return true;
    }
    return false;
}

void changePassword(vector<Account> accounts, Account &account) {
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
            ofstream ofs("SignUp.txt");
            if (!ofs.is_open())
                return;
            
            for (int i = 0; i < accounts.size(); i++) {
                if (accounts[i].username == account.username) {
                    ofs << account.username << " " << account.password << endl;
                } else {
                    ofs << accounts[i].username << " " << accounts[i].password << endl;
                }
            }

            cout << "Your password has successfully changed!" << endl;
            ofs.close();
        }
    }
}