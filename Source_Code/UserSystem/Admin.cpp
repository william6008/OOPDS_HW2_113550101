
#include <iostream>
#include <string>
#include <set>
#include "Admin.h"
#include "../Classes/Library.h"
#include "../Classes/InputSystem.h"

Admin::Admin(User& user) {
    this->account = user.getAccount();
    this->password = user.getPassword();
    this->isAdmin = 1;
}

void Admin::interface() {
    cout << "Welcome to the admin Interface" << endl;
    Library library(*this);
    library.load(); 
    string op;
    while (op != "exit") {
        op = input(set<string>{"add", "remove", "list", "exit"}, "Type 'help' to view commands.");
        if (op == "add") {
            library.addBook();
        } else if (op == "remove") {
            //library.removeCopy();
        } else if (op == "list") {
            //library.listAllBooks();
        } else if (op == "exit") {
            cout << "Exiting admin interface." << endl;
        }
    }

}