#include "account.cpp"

int main() {
    // Load accounts and weak passwords from files
    vector<Account> accounts = loadAccounts();
    vector<string> weakPasswords = loadWeakPasswords();

    // Display menu and get user choice
    int choice;
    cout << "1. Registration\n"
         << "2. Multiple Registrations\n"
         << "3. Log-in\n"
         << "4. Change Password\n"
         << "5. Exit\n"
         << "Enter your choice: ";
    cin >> choice;

    cin.ignore(); // Clear the newline character from the buffer

    switch (choice) {
        case 1: // Registration
            registerAccount(accounts, weakPasswords);
            break;
        case 2: // Multiple Registrations
            multipleRegistrations(accounts, weakPasswords);
            break;
        case 3: // Log-in
            login(accounts);
            break;
        case 4: // Change Password
            {
                string username;
                cout << "Enter your username: ";
                getline(cin, username);
                for (Account& acc : accounts) {
                    if (acc.username == username) {
                        changePassword(accounts, weakPasswords, acc);
                        break;
                    }
                }
            }
            break;
        case 5: // Exit
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
    }

    return 0;
}
