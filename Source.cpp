/*
This program is to keep track of bills
There is a main menu implemented in Source.cpp this handles displaying menu items and connecting to the Bills and SearchBills classes
The Bills class handles all bill information and reading and writing information to the bills.txt file.
The SearchBills class handles searching the bills by name, amount, due date, or status

Missing Functions:  Notifications to let the user know a bill is due,  totaling the amount due per month and per year.

*/
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Bills.h" 

using namespace std;

void printMenu();
void addBill(vector<Bill>& bills);
void editBill(vector<Bill>& bills);
void searchBill(const vector<Bill>& bills);
void displayBills(const vector<Bill>& bills);

int main() {
    // Reads the list of bills from the file "bills.txt" and stores them in a vector of bills.
    vector<Bill> bills = Bill::readBillsFromFile("bills.txt");

    int menuChoice = -1;
    // Loop that displays the main menu until the user chooses to exit.
    while (menuChoice != 0) {
        printMenu();
        cin >> menuChoice;

        switch (menuChoice) {
        case 1:
            addBill(bills);
            break;
        case 2:
            editBill(bills);
            break;
        case 3:
            searchBill(bills);
            break;
        case 4:
            displayBills(bills);
            break;
        case 0:
            // Writes the list of bills to the file "bills.txt" and exits the program.
            Bill::writeBillsToFile(bills, "bills.txt");
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

//Function to display the main menu to the user
void printMenu() {
    cout << "Main menu:" << endl;
    cout << "1. Add a new bill" << endl;
    cout << "2. Edit a bill" << endl;
    cout << "3. Search bills" << endl;
    cout << "4. Display bills" << endl;
    cout << "0. Exit Program" << endl;
}

//Function to display the search submenu
void printSearchMenu() {
    cout << "Search bills by:" << endl;
    cout << "1. Name" << endl;
    cout << "2. Amount" << endl;
    cout << "3. Due date" << endl;
    cout << "4. Paid status" << endl;
    cout << "5. Go back to main menu" << endl;
}

//Function to add new bills, prompts the user for bill information
void addBill(vector<Bill>& bills) {
    string name, date;
    double amount;
    string isPaid;

    cout << "Enter bill name: ";
    cin >> name;

    cout << "Enter bill amount: ";
    cin >> amount;

    cout << "Enter due date (MM/DD/YYYY): ";
    cin >> date;

    cout << "Is the bill paid? (y/n): ";
    cin >> isPaid;
    isPaid = (isPaid == "y" || isPaid == "Y") ? "paid" : "unpaid";

    Bill bill(name, amount, date, isPaid == "paid");
    bills.push_back(bill);

    cout << "Bill added successfully." << endl;
}

//Function to edit existing bills
void editBill(vector<Bill>& bills) {
    string name;
    cout << "Enter the name of the bill to edit: ";
    cin >> name;

    bool billFound = false;
    for (auto& bill : bills) {
        if (bill.getname() == name) {
            billFound = true;
            string input;
            double amount;
            string date, isPaid;

            cout << "Enter new bill name (leave blank to keep current name): ";
            cin.ignore();
            getline(cin, input);
            if (!input.empty()) {
                bill.setbillInfo(input, bill.getamount(), bill.getDate(), bill.isPaid());
            }

            cout << "Enter new bill amount (leave blank to keep current amount): ";
            getline(cin, input);
            if (!input.empty()) {
                amount = stod(input);
                bill.setbillInfo(bill.getname(), amount, bill.getDate(), bill.isPaid());
            }

            cout << "Enter new due date (MM/DD/YYYY) (leave blank to keep current due date): ";
            getline(cin, input);
            if (!input.empty()) {
                bill.setbillInfo(bill.getname(), bill.getamount(), input, bill.isPaid());
            }

            cout << "Is the bill paid? (y/n) (leave blank to keep current status): ";
            getline(cin, input);
            if (!input.empty()) {
                isPaid = (input == "y" || input == "Y") ? "paid" : "unpaid";
                bill.setbillInfo(bill.getname(), bill.getamount(), bill.getDate(), isPaid);
            }

            cout << "Bill edited successfully." << endl;
            break;
        }

    }
}

//Function to search for bills, prompts the user to choose what to search by
void searchBill(const vector<Bill>& bills) {
    int searchOption;
    string searchTerm;
    double searchAmount;
    bool foundBills = false;

    cout << "\nSearch for Bills\n";
    cout << "-----------------\n";
    cout << "1. Search by Name\n";
    cout << "2. Search by Amount\n";
    cout << "3. Search by Due Date\n";
    cout << "4. Search by Paid Status\n";
    cout << "5. Display All Bills\n";
    cout << "0. Back\n";

    cout << "\nEnter option: ";
    cin >> searchOption;

    switch (searchOption) {
    case 1: // Search by Name
        cout << "Enter bill name: ";
        cin >> searchTerm;
        {
            vector<Bill> matchingBills = BillSearch::searchByName(bills, searchTerm);
            if (matchingBills.empty()) {
                cout << "\nNo bills found for name: " << searchTerm << endl;
            }
            else {
                foundBills = true;
                cout << "\nBills found for name: " << searchTerm << endl;
                displayBills(matchingBills);
            }
        }
        break;

    case 2: // Search by Amount
        cout << "Enter bill amount: ";
        cin >> searchAmount;
        {
            vector<Bill> matchingBills = BillSearch::searchByAmount(bills, searchAmount);
            if (matchingBills.empty()) {
                cout << "\nNo bills found for amount: " << searchAmount << endl;
            }
            else {
                foundBills = true;
                cout << "\nBills found for amount: " << searchAmount << endl;
                displayBills(matchingBills);
            }
        }
        break;

    case 3: // Search by Due Date
        cout << "Enter due date (MM/DD/YYYY): ";
        cin.ignore(); // ignore previous newline character
        getline(cin, searchTerm);
        {
            vector<Bill> matchingBills = BillSearch::searchByDate(bills, searchTerm);
            if (matchingBills.empty()) {
                cout << "\nNo bills found for due date: " << searchTerm << endl;
            }
            else {
                foundBills = true;
                cout << "\nBills found for due date: " << searchTerm << endl;
                displayBills(matchingBills);
            }
        }
        break;

    case 4: // Search by Paid Status
        cout << "Enter paid status (paid/unpaid): ";
        cin >> searchTerm;
        {
            vector<Bill> matchingBills = BillSearch::searchByPaidStatus(bills, searchTerm);
            if (matchingBills.empty()) {
                cout << "\nNo bills found for paid status: " << searchTerm << endl;
            }
            else {
                foundBills = true;
                cout << "\nBills found for paid status: " << searchTerm << endl;
                displayBills(matchingBills);
            }
        }
        break;

    case 5: // Display All Bills
        if (bills.empty()) {
            cout << "\nNo bills found.\n";
        }
        else {
            foundBills = true;
            displayBills(bills);
        }
        break;

    case 0: // Back
        return;

    default:
        cout << "\nInvalid option. Please try again.\n";
        break;
    }
}

    //Function to display the bills from search
    void displayBills(const vector<Bill>&bills) {
        cout << "--------------------------------------------------------\n";
        cout << "Bills:\n";
        cout << "--------------------------------------------------------\n";

        for (const auto& bill : bills) {
            cout << "Bill Name: " << bill.getname() << "\n";
            cout << "Bill Amount: $" << bill.getamount() << "\n";
            cout << "Due Date: " << bill.getDate() << "\n";
            cout << "Paid Status: " << bill.isPaid() << "\n";
            cout << "--------------------------------------------------------\n";
        }
    }


