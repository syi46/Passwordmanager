#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

const string FILENAME = "passwords.txt";

void showMenu() {
    cout << "Password Management System" << endl;
    cout << "---------------------------" << endl;
    cout << "1. Add a new password" << endl;
    cout << "2. Retrieve a password" << endl;
    cout << "3. Delete a password" << endl;
    cout << "4. Exit" << endl;
    cout << "Choose an option: ";
}

void loadPasswords(map<string, string> &passwords) {
    ifstream infile(FILENAME);
    if (!infile) {
        cout << "No existing passwords found. Starting fresh." << endl;
        return;
    }

    string site, password;
    while (infile >> site >> password) {
        passwords[site] = password;
    }
    infile.close();
}

void savePasswords(const map<string, string> &passwords) {
    ofstream outfile(FILENAME);
    for (const auto &entry : passwords) {
        outfile << entry.first << " " << entry.second << endl;
    }
    outfile.close();
}

void addPassword(map<string, string> &passwords) {
    string site, password;
    cout << "Enter the site name: ";
    cin >> site;
    cout << "Enter the password: ";
    cin >> password;

    passwords[site] = password;
    savePasswords(passwords);
    cout << "Password saved successfully!" << endl;
}

void retrievePassword(const map<string, string> &passwords) {
    string site;
    cout << "Enter the site name: ";
    cin >> site;

    auto it = passwords.find(site);
    if (it != passwords.end()) {
        cout << "Password for " << site << ": " << it->second << endl;
    } else {
        cout << "No password found for " << site << endl;
    }
}

void deletePassword(map<string, string> &passwords) {
    string site;
    cout << "Enter the site name: ";
    cin >> site;

    if (passwords.erase(site)) {
        savePasswords(passwords);
        cout << "Password deleted successfully!" << endl;
    } else {
        cout << "No password found for " << site << endl;
    }
}

int main() {
    map<string, string> passwords;
    loadPasswords(passwords);

    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addPassword(passwords);
                break;
            case 2:
                retrievePassword(passwords);
                break;
            case 3:
                deletePassword(passwords);
                break;
            case 4:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please choose a valid option." << endl;
                break;
        }

        cout << endl;
    }

    return 0;
}

