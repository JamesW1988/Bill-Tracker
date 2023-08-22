#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Bill {
public:
    // set bill information
    void setbillInfo(string name, double amount, string date, string isPaid) {
        billName = name;
        billAmount = amount;
        dueDate = date;
        paid = isPaid;
    }

    // get bill name
    string getname() const {
        return billName;
    }

    // get bill amount
    double getamount() const {
        return billAmount;
    }

    // get bill due date
    string getDate() const {
        return dueDate;
    }

    // get bill paid status
    string isPaid() const {
        return paid;
    }

    // check if bill is due
    bool isDue() const {
        // TODO: implement date comparison logic
        return false;
    }

    // write bills to a file
    static void writeBillsToFile(const vector<Bill>& bills, const string& filename) {
        ofstream outfile(filename);
        if (!outfile) {
            cerr << "Error: could not open file " << filename << " for writing\n";
            return;
        }
        for (const auto& bill : bills) {
            outfile << bill.billName << '\t' << bill.billAmount << '\t' << bill.dueDate << '\t' << bill.paid << '\n';
        }
    }

    //read bills from file
    static vector<Bill> readBillsFromFile(const string& filename) {
        vector<Bill> bills;
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error: could not open file " << filename << " for reading\n";
            return bills;
        }
        string name, date, line, isPaidStr;
        double amount;
        while (getline(infile, line)) {
            istringstream iss(line);
            if (!(iss >> name >> amount >> date >> isPaidStr)) {
                cerr << "Error: could not read bill from line '" << line << "'\n";
                continue;
            }
            bool isPaid = (isPaidStr == "paid");
            bills.emplace_back(name, amount, date, isPaid);
        }
        // sort bills by due date
        sort(bills.begin(), bills.end(), [](const Bill& a, const Bill& b) {
            return a.getDate() < b.getDate();
            });
        return bills;
    }


    // constructor
    Bill(const string& name, double amount, const string& date, bool isPaid = false)
        : billName(name), billAmount(amount), dueDate(date), paid(isPaid ? "paid" : "unpaid") {
    }


private:
    string billName;
    double billAmount;
    string dueDate;
    string paid;
};

class BillSearch {
public:
    // search bills by name
    static vector<Bill> searchByName(const vector<Bill>& bills,  string& name) {
        vector<Bill> result;
        for (const auto& bill : bills) {
            if (bill.getname() == name) {
                result.push_back(bill);
            }
        }
        return result;
    }

    // search bills by amount
    static vector<Bill> searchByAmount(const vector<Bill>& bills, double amount) {
        vector<Bill> result;
        for (const auto& bill : bills) {
            if (bill.getamount() == amount) {
                result.push_back(bill);
            }
        }
        return result;
    }

    // search bills by due date
    static vector<Bill> searchByDate(const vector<Bill>& bills,  string& date) {
        vector<Bill> result;
        for (const auto& bill : bills) {
            if (bill.getDate() == date) {
                result.push_back(bill);
            }
        }
        return result;
    }

    //Search bills by paid status
    static vector<Bill> searchByPaidStatus(const vector<Bill>& bills,  string& paidStatus) {
        vector<Bill> result;
        for (const auto& bill : bills) {
            if (bill.isPaid().compare(paidStatus) == 0) {
                result.push_back(bill);
            }
        }
        return result;
    }

};




