#include <iostream>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <ctime>
#include "../Classes/Library.h"
#include "../Classes/Book.h"
#include "../Classes/BookCopy.h"
#include "User.h"
#include "Reader.h"
#include "../Classes/InputSystem.h"

Reader::Reader(User& user) {
    this->account = user.getAccount();
    this->password = user.getPassword();
    this->isAdmin = 0;
}

void Reader::interface() {
    cout << "Welcome to the reader interface!" << endl;
    Library library(*this);
    library.load();
    string op;
    while (op != "exit") {
        op = input(set<string>{"search", "checkout", "return", "list", "exit"}, "Type 'help' to view commands.");
        if (op == "search") {
            //library.searchByTitle();
        } else if (op == "checkout") {
            //library.checkOutBook();
        } else if (op == "return") {
            //library.returnBook();
        } else if (op == "list") {
            library.listAllBooks();
        } else if (op == "exit") {
            cout << "Exiting reader interface." << endl;
        }
    }
}

void Reader::load() {
    ifstream in;
    in.open("ReaderFile\\" + this->account + ".txt");
    if (!in) {
        cout << "Unable to open the file!!!" << endl;
        throw "Unable to open the file!!!";
    }
    in >> this->checkedOutCount;
    for (int i = 0; i < this->checkedOutCount; i++) {
        int ID;
        tm due_date = {};
        int parentBookIndex;

        in >> ID;
        in.ignore(1, '|');
        in >> due_date.tm_year;
        in.ignore(1, '|');
        in >> due_date.tm_mon;
        in.ignore(1, '|');
        in >> due_date.tm_mday;
        in.ignore(1, '|');
        in >> parentBookIndex;
        in.ignore(1, '\n');
        checkedOutBooks.push_back(BookCopy(ID, due_date, parentBookIndex));
    }
    in.close();
    return;
}

void Reader::save() {
    ofstream out;
    out.open("ReaderFile\\" + this->account + ".txt", ios::trunc);
    if (!out) {
        cout << "Unable to open the file!!!" << endl;
        throw "Unable to open the file!!!";
    }
    out << this->checkedOutCount << endl;
    for (auto& it : checkedOutBooks) {
        out << it.ID << "|" << it.due_date.tm_year << "|" << it.due_date.tm_mon << "|" << it.due_date.tm_mday << "|" << it.parentBookIndex;
        out << endl;
    }
    out.close();
    return;
}
