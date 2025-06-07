#include <iostream>
#include <string>
#include "UserSystem/User.h"
#include "Classes/Book.h"
#include "Classes/BookCopy.h"
#include "Classes/Library.h"
#include "Helper/Helper.h"

using namespace std;

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
    }

    if (user.getIsAdmin()) user.adminInterface();
    else user.readerInterface();

    return 0;

}
