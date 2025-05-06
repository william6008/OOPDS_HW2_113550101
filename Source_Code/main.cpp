#include <iostream>
#include <string>
#include "UserSystem/User.h"
#include "Classes/Book.h"
#include "Classes/BookCopy.h"
#include "Classes/Library.h"
#include "Classes/InputSystem.h"

using namespace std;

int main() {
    User user;
    cout << "Welcome to the Library Management System!" << endl;
    string choice;
    bool done = 0;
    while (!done) {
        cout << "Whould you like to login(L) or register(R)?" << endl;
        input(set<string>{"l", "r"}, "Ivalid input. Please enter 'login' or 'register'.");
        
        if (choice == "l") done = user.login();
        else if (choice == "r") done = user.registerUser();   
    }

    if (user.getIsAdmin()) user.adminInterface();
    else user.readerInterface();

    return 0;

}
    