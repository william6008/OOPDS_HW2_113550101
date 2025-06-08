#include <iostream>
#include <string>
#include "UserSystem/User.h"
#include "Classes/Book.h"
#include "Classes/BookCopy.h"
#include "Classes/Library.h"
#include "Helper/Helper.h"

using namespace std;

void adminInterface(Library& library) {
    clearScreen();
    type("Welcome to the admin Interface\n", 1);
    int op = -1;
    enum status {DEFAULT, VIEW};
    status current = DEFAULT;
    while (op != 0) {
        switch (current) {
            case DEFAULT:
                type("Please choose an option:\n", 1);
                type("1. Add a book\n2. Search for a book\n3. List all books\n0. Exit\n", 1);
                cin >> op;
                switch (op) {
                    case 1:
                        library.addBook();
                        break;
                    case 2:
                        library.search();
                        current = VIEW;
                        break;
                    case 3:
                        library.listAllBooks("");
                        current = VIEW;
                        break;
                    case 0:
                        return;
                    default:
                        type("Invalid command. Please try again.\n", 1);
                }
                break;
            case VIEW:
                type("Please choose an option:\n", 1);
                type("1. Add a book\n2. Search for a book\n3. List all books\n4. Change the quantity of copies\n0. Exit\n", 1);
                cin >> op;
                switch (op) {
                    case 1:
                        library.addBook();
                        break;
                    case 2:
                        library.search();
                        break;
                    case 3:
                        library.listAllBooks("");
                        break;
                    case 4:
                        library.changeQuantity();
                        break;
                    case 0:
                        return;
                    default:
                        type("Invalid command. Please try again.\n", 1);

                }
                break;
        }
    }

}

void readerInterface(Library& library) {
    enum status {SEARCH, MYBOOKS};
    status current = MYBOOKS;
    int op = -1;
    library.showMyBooks();
    while (op != 0) {
        switch (current) {
            case MYBOOKS:
                type("Please choose an option:\n", 1);
                type("1. Search for a book\n2. List all books\n3. Return books\n0. Exit\n", 1);
                cin >> op;
                switch (op) {
                    case 1:
                        library.search();
                        current = SEARCH;
                        break;
                    case 2:
                        library.listAllBooks();
                        current = SEARCH;
                        break;
                    case 3:
                        library.returnBook();
                        current = MYBOOKS;
                        break;
                    case 0:
                        return;
                    default:
                        type("Invalid command. Please try again.\n", 1);
                }
                break;
            case SEARCH:
                type("Please choose an option:\n", 1);
                type("1. Search for a book\n2. List all books\n3. Check out a book\n4. Show my books\n0. Exit\n", 1);
                cin >> op;
                switch (op) {
                    case 1:
                        library.search();
                        current = SEARCH;
                        break;
                    case 2:
                        library.listAllBooks();
                        current = SEARCH;
                        break;
                    case 3:
                        library.checkOutBook();
                        current = SEARCH;
                        break;
                    case 4:
                        library.showMyBooks();
                        current = MYBOOKS;
                        break;
                    case 0:
                        return;
                    default:
                        type("Invalid command. Please try again.\n", 1);
                }
                break;
       
        }
    }
}



int main() {
    User user;
    type("Welcome to the Library Management System!\n", 1);
    string choice;
    bool done = 0;
    while (!done) {
        type("Whould you like to login(L) or register(R)?\n", 1);
        choice = input(set<string>{"l", "r"}, "Please enter 'login' or 'register'.");
        
        if (choice == "l") done = user.login();
        else if (choice == "r") done = user.registerUser();   
        if (done) break;
        delay(10);
        clearScreen();
    }
    Library library(user);
    if (user.getIsAdmin()) adminInterface(library);
    else readerInterface(library);

    return 0;

}
