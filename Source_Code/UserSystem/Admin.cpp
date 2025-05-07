
#include <iostream>
#include <string>
#include <set>
#include "Admin.h"
#include "../Classes/Library.h"
#include "../Classes/InputSystem.h"


void User::interface() {
    cout << "Welcome to the admin Interface" << endl;
    Library library(1);
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