#include <iostream>
#include <string>
#include <set>
#include "../Classes/Library.h"
#include "User.h"
#include "Reader.h"
#include "../Classes/InputSystem.h"

Reader::Reader(User& user) {
    this->account = user.getAccount();
    this->password = user.getPassword();
    this->isAdmin = 0;
}

void User::interface() {
    cout << "Welcome to the reader interface!" << endl;
    Library library(0);
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