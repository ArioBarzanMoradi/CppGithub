#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

struct Contact {
    string firstName;
    string lastName;
    string phoneNumber;
    string email;
};

class ContactManager {
private:
    vector<Contact> contacts;
    const string filename = "contacts.txt";

    void saveToFile() {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.firstName << ","
                     << contact.lastName << ","
                     << contact.phoneNumber << ","
                     << contact.email << endl;
            }
            file.close();
        } else {
            cerr << "Error: Nemitavan file ra baz kard!" << endl;
        }
    }

public:
    ContactManager() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string fName, lName, phone, mail;

                if (getline(ss, fName, ',') &&
                    getline(ss, lName, ',') &&
                    getline(ss, phone, ',') &&
                    getline(ss, mail)) {

                    contacts.push_back({fName, lName, phone, mail});
                }
            }
            file.close();
        }
    }

    void addContact() {
        Contact newContact;
        cout << "\n--- Afzoodan Mokhatab Jadid ---\n";
        cout << "Nam: "; cin >> newContact.firstName;
        cout << "Family: "; cin >> newContact.lastName;
        cout << "Mobile: "; cin >> newContact.phoneNumber;
        cout << "Email: "; cin >> newContact.email;

        contacts.push_back(newContact);
        saveToFile();
        cout << ">> Mokhatab ba movafaghiat ezafe shod.\n";
    }

    void displayContacts() {
        if (contacts.empty()) {
            cout << "\n>> List mokhatabin khali ast.\n";
            return;
        }

        cout << "\n----------------------------------------------------------------------\n";
        cout << left << setw(15) << "Nam"
             << setw(20) << "Family"
             << setw(15) << "Mobile"
             << setw(25) << "Email" << endl;
        cout << "----------------------------------------------------------------------\n";

        for (const auto& c : contacts) {
            cout << left << setw(15) << c.firstName
                 << setw(20) << c.lastName
                 << setw(15) << c.phoneNumber
                 << setw(25) << c.email << endl;
        }
        cout << "----------------------------------------------------------------------\n";
    }

    void searchContact() {
        string query;
        cout << "\nNam ya Mobile ra baraye jostojoo vared konid: ";
        cin >> query;

        bool found = false;
        cout << "\n--- Natayej Jostojoo ---\n";
        for (const auto& c : contacts) {
            if (c.firstName == query || c.lastName == query || c.phoneNumber == query) {
                cout << "Nam: " << c.firstName << " " <<
                        "| family:" << " " << c.lastName
                     << " | Mobile: " << c.phoneNumber
                     << " | Email: " << c.email << endl;
                found = true;
            }
        }

        if (!found) cout << ">> Hich moredi yaft nashod.\n";
    }

    void editContact() {
        string phone;
        cout << "\nMobile mokhatab ra baraye virayesh vared konid: ";
        cin >> phone;

        for (auto& c : contacts) {
            if (c.phoneNumber == phone) {
                cout << "Yaft shod: " << c.firstName << " " << c.lastName << endl;

                string input;
                cout << "Nam Jadid (ya . baraye bedoon taghir): ";
                cin >> input; if(input != ".") c.firstName = input;

                cout << "Family Jadid (ya . baraye bedoon taghir): ";
                cin >> input; if(input != ".") c.lastName = input;

                cout << "Mobile Jadid (ya . baraye bedoon taghir): ";
                cin >> input; if(input != ".") c.phoneNumber = input;

                cout << "Email Jadid (ya . baraye bedoon taghir): ";
                cin >> input; if(input != ".") c.email = input;

                saveToFile();
                cout << ">> Ettelaat update shod.\n";
                return;
            }
        }
        cout << ">> Mokhatabi ba in shomare yaft nashod.\n";
    }

    void deleteContact() {
        string phone;
        cout << "\nMobile mokhatab ra baraye hazf vared konid: ";
        cin >> phone;

        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->phoneNumber == phone) {
                char confirm;
                cout << "Aya motmaen hastid ke " << it->firstName << " hazf shavad? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y') {
                    contacts.erase(it);
                    saveToFile();
                    cout << ">> Mokhatab hazf shod.\n";
                } else {
                    cout << ">> Amaliat cancel shod.\n";
                }
                return;
            }
        }
        cout << ">> Mokhatabi ba in shomare yaft nashod.\n";
    }
};

int main() {
    ContactManager cms;
    int choice;

    do {
        cout << "\n======================================\n";
        cout << "   System Modiriat Mokhatabin (CMS)\n";
        cout << "======================================\n";
        cout << "1. Afzoodan Mokhatab (Add)\n";
        cout << "2. Namayesh List (List)\n";
        cout << "3. Jostojoo (Search)\n";
        cout << "4. Virayesh (Edit)\n";
        cout << "5. Hazf (Delete)\n";
        cout << "0. Khorooj (Exit)\n";
        cout << "Entekhab Shoma: ";
        cin >> choice;

        switch (choice) {
            case 1: cms.addContact(); break;
            case 2: cms.displayContacts(); break;
            case 3: cms.searchContact(); break;
            case 4: cms.editContact(); break;
            case 5: cms.deleteContact(); break;
            case 0: cout << "Bye Bye!\n"; break;
            default: cout << "Gozine namotabar ast (Invalid)!\n";
        }
    } while (choice != 0);

    return 0;
}