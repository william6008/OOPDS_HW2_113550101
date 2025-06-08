#include<fstream>
#include<iostream>
#include<string>
#include <conio.h>
#include "User.h"
#include "../Helper/Helper.h"

using namespace std;



string User::getAccount() {
    return this->account;
}

string User::getPassword() {
    return this->password;
}

bool User::getIsAdmin() {
    return this->isAdmin;
}



bool User::login() {

    string account;
    string correctPassword;

    //user enters account
    type("Please enter your username: \n", 1);
    cin >> account;
    
    if (account == "admin") {
        correctPassword = "admin"; 
        ifstream in;
        in.open("ReaderFile\\" + account + ".txt");
        if (!in) {
            type("User not found.\n", 1);
            type("Press any key to continue.\n", 1);
            _getch(); 
            return 0;
        }
    
        in >> correctPassword;
        in.close();
    }
    

    //user enters password
    string password;
    type("Please enter your password: \n", 1);
    cin >> password;
    
    if (password == correctPassword) {
        this->account = account;
        this->password = password;
        if (account == "admin") {
            isAdmin = 1;
            return 1;
        } else {
            type("Login successful!\n", 1);
            type("Welcome back, " + account + "!\n", 1);
            isAdmin = 0;
            ifstream in;
            in.open("ReaderFile\\" + account + ".txt");
            in.ignore(1000, '\n');
            delay(50); 
            return 1;
        }
    }
    else {
        type("Incorrect password.\n", 1);
        type("Press any key to continue.\n", 1);
        _getch(); 
        return 0;
    }
}

bool User::registerUser() {
    //user enters account
    string account;
    type("Please set up your username: \n", 1);
    cin >> account;
    ifstream in;
    in.open("ReaderFile\\" + account + ".txt");
    if (in || account == "admin") {
        type("Username already exists.\n", 1);
        type("Press any key to continue.\n", 1);
        _getch(); 
        return 0;
    }
    
    //user enters password
    string password;
    type("Please set up your password: \n", 1);
    cin >> password;
    
    //create account
    this->account = account;
    this->password = password;
    ofstream out;
    out.open("ReaderFile\\" + account + ".txt");
    if (!out) {
        type("Unable to open the file!!!\n", 1);
        return 0;
    }
    else {

    }
    
    type("Account created!\n", 1);
    delay(50);
    out << password << endl;
    out << 0 << endl; 
    out.close();
    this->isAdmin = 0;
    return 1;
}



