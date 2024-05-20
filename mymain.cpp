#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

class Loan {
private:
    int Id;
    string Name;
    string product;
    float Amount;
    float interest;
    int time;
    string pnum;
public:
 void addloan(int id) {
        Id = id;
        cout << "Enter Farmer's Name: ";
        cin >> ws;
        getline(cin, Name);

        cout << "Enter Product: ";
        getline(cin, product);

        cout << "Enter Loan Amount: ";
        cin >> Amount;

        if (Amount <= 50000) {
            interest = 5.0; 
        } else {
            interest = 7.5; 
        }

        cout << "Enter Loan Duration (in years): ";
        cin >> time;

        bool validPhoneNumber = false;
        do {
            cout << "Enter Phone Number (10 digits starting with 5, 6, 7, 8, or 9): ";
            cin >> pnum;

            if (pnum.length() == 10 && (pnum[0] == '5' || pnum[0] == '6' || pnum[0] == '7' || pnum[0] == '8' || pnum[0] == '9')) {
                validPhoneNumber = true;
            } else {
                cout << "Invalid phone number format! Please enter a 10-digit number starting with 5, 6, 7, 8, or 9." << endl;
            }
        } while (!validPhoneNumber);

        savefile();
    }

float installment() const {
        int totalMonths = time * 12;
        float monthlyinterest = interest / 100 / 12;
        float totalAmount = Amount * (1 + monthlyinterest * totalMonths);
        return totalAmount / totalMonths;
    }
void displayAllLoans() {
    ifstream file("loans.txt");

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    bool dataFound = false;
    while (getline(file, line)) {
        if (line == "------------------------") {
            cout << endl;
        }
        cout << line << endl;
        dataFound = true;
    }

    file.close();

    if (!dataFound) {
        cout << "No data found!" << endl;
    }
}
void displayloan() const {
        cout << "Loan ID: " << Id << endl;
        cout << "Farmer's Name: " << Name << endl;
        cout << "Product: " << product << endl;
        cout << "Loan Amount: " << Amount << endl;
        cout << "Interest Rate: " << interest << "%" << endl;
        cout << "Loan Duration: " << time << " years" << endl;
        cout << "Monthly Installment: " << installment() << endl;
        cout << "Phone Number: " << pnum << endl;
        cout << "------------------------" << endl;
    }
void savefile() const {
        ofstream file("loans.txt", ios::app);

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        file << "Loan ID: " << Id << endl;
        file << "Farmer's Name: " << Name << endl;
        file << "Product: " << product << endl;
        file << "Loan Amount: " << Amount << endl;
        file << "Interest Rate: " << interest << "%" << endl;
        file << "Loan Duration: " << time << " years" << endl;
        file << "Monthly Installment: " << installment() << endl;
        file << "Phone Number: " << pnum << endl;
        file << "------------------------" << endl;

        file.close();
    }
void updateloan(int id) {
        ifstream read("loans.txt");
        ofstream write("temp.txt");

        if (!read.is_open() || !write.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(read, line)) {
            if (line.find("Loan ID: " + to_string(id)) != string::npos) {
                found = true;
                write << "Loan ID: " << id << endl;
                cout << "Enter Farmer's Name: ";
                cin >> Name;
                write << "Farmer's Name: " << Name << endl;

                cout << "Enter Product: ";
                cin >> product;
                write << "Product: " << product << endl;

                cout << "Enter Loan Amount: ";
                cin >> Amount;
                write << "Loan Amount: " << Amount << endl;

                if (Amount <= 10000) {
                    interest = 5.0;
                } else {
                    interest = 7.5;
                }
                write << "Interest Rate: " << interest << "%" << endl;

                cout << "Enter Loan Duration (in years): ";
                cin >> time;
                write << "Loan Duration: " << time << " years" << endl;

                bool validpnum = false;
                do {
                    cout << "Enter Phone Number (10 digits starting with 5, 6, 7, 8, or 9): ";
                    cin >> pnum;

                    if (pnum.length() == 10 && (pnum[0] == '5' || pnum[0] == '6' || pnum[0] == '7' || pnum[0] == '8' || pnum[0] == '9')) {
                        validpnum = true;
                    } else {
                        cout << "Invalid phone number format!" << endl;
                    }
                } while (!validpnum);
                write << "Phone Number: " << pnum << endl;

                write << "Monthly Installment: " << installment() << endl;
                write << "------------------------" << endl;
                for (int i = 0; i < 8; ++i) {
                    getline(read, line);
                }
            } else {
                write << line << endl;
            }
        }

        read.close();
        write.close();

        remove("loans.txt");
        rename("temp.txt", "loans.txt");

        if (found) {
            cout << "Loan with ID " << id << " updated successfully!" << endl;
        } else {
            cout << "Loan with ID " << id << " not found!" << endl;
        }
    }
void deleteLoan(int id) {
        ifstream dlr("loans.txt");
        ofstream dlw("temp.txt");

        if (!dlr.is_open() || !dlw.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(dlr, line)) {
            if (line.find("Loan ID: " + to_string(id)) != string::npos) {
                found = true;
                for (int i = 0; i < 8; ++i) { 
                    getline(dlr, line);
                }
            } else {
                dlw << line << endl;
            }
        }

        dlr.close();
        dlw.close();

        remove("loans.txt");
        rename("temp.txt", "loans.txt");

        if (found) {
            cout << "Loan with ID " << id << " deleted successfully!" << endl;
        } else {
            cout << "Loan with ID " << id << " not found!" << endl;
        }
    }
void searchLoan(int id) {
        ifstream file("loans.txt");

        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line)) {
            if (line.find("Loan ID: " + to_string(id)) != string::npos) {
                found = true;
                cout << "Loan Found:" << endl;
                while (line != "------------------------") {
                    cout << line << endl;
                    getline(file, line);
                }
                break;
            }
        }

        file.close();

        if (!found) {
            cout << "Loan with ID " << id << " not found!" << endl;
        }
    }
string passhider() {
    const char BACKSPACE = 8;
    const char ENTER = 13;

    string password;
    char ch = 0;

    while ((ch = _getch()) != ENTER) {
        if (ch == BACKSPACE) {
            if (password.length() != 0) {
                cout << "\b \b";
                password.pop_back(); //removes last character
            }
        } else {
            password += ch;
            cout << '*'; // Print asterisks (*) instead of actual characters
        }
    }

    cout << endl;
    return password;
}
void adminLogin() {
        string adminPassword;
        cout << "Enter admin password: ";
        adminPassword = passhider();

        if (adminPassword == "clgproject") {
            adminMenu();
        } else {
            cout << "Invalid password! Access denied." << endl;
        }
    }
int ridcount() {
    ifstream counterFile("loan_counter.txt");
    int counter = 1;
    if (counterFile.is_open()) {
        counterFile >> counter;
        counterFile.close();
    }
    return counter;
}
void adminMenu() {
    int id = ridcount();

    int adminChoice;
    do {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Loan\n2. Update Loan\n3. Delete Loan\n4. Display All Loans\n5. Search for a Specific Loan\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> adminChoice;

        switch (adminChoice) {
            case 1: {
                addloan(id);
                break;
            }
                case 2: {
                int id;
                cout << "Enter Loan ID to update: ";
                cin >> id;
                updateloan(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Loan ID to delete: ";
                cin >> id;
                deleteLoan(id);
                break;
            }
            case 4:
                displayAllLoans();
                break;
            case 5: {
                int id;
                cout << "Enter Loan ID to search: ";
                cin >> id;
                searchLoan(id);
                break;
            }
                case 6:
                    cout << "Exiting admin panel..." << endl;
                    return;
                default:
                    cout << "Invalid choice! Please enter a valid option." << endl;
            }
        } while (adminChoice != 8);
    }
};

int main() {
    Loan loan;
    int loginChoice;
    do{
    cout<<"\n************************************************************\n";
    cout << "AGRICULTURE FINANCES MANAGEMENT SYSTEM\n";
    cout<<"************************************************************\n";
    cout << "Login as:\n1. Admin\n2. Exit\nEnter your choice: ";
    cin >> loginChoice;

    switch (loginChoice) {
        case 1:
            loan.adminLogin();
            break;
        case 2:
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Invalid choice! Exiting the program..." << endl;
    }} while (loginChoice!=3);

    return 0;
}
