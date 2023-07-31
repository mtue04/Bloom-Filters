#include "account.cpp"

using namespace std;

int main()
{
    Account account;
    vector<Account> accounts;
    loadWeakPasswords();

    char choice;
    do
    {
        cout << "========================" << endl;
        cout << "1. Register Account" << endl;
        cout << "2. Multiple Registrations" << endl;
        cout << "3. Log-in" << endl;
        cout << "4. Exit" << endl;
        cout << "========================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case '1':
            registerAccount(accounts);
            break;
        case '2':
            multipleRegistrations(accounts);
            break;
        case '3':
            if (login(accounts, account))
            {
                while (choice != '2')
                {
                    cout << "========================" << endl;
                    cout << "1. Change Password" << endl;
                    cout << "2. Log-out" << endl;
                    cout << "========================" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case '1':
                        changePassword(accounts, account);
                        break;
                    case '2':
                        cout << "Logging out . . ." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            break;
        case '4':
        {
            string username;
            cout << "Enter your username: ";
            getline(cin, username);
            for (Account &acc : accounts)
            {
                if (isUserExists(acc.username))
                {
                    changePassword(accounts, acc);
                    break;
                }
            }
        }
        break;
        case '5':
            cout << "Exiting program . . ." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != '4');

    return 0;
}
