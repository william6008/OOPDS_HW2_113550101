#include<fstream>
#include<iostream>
#include<string>
#include<set>
#include "../Classes/Library.h"
#include "../Classes/InputSystem.h"
#include "User.h"

using namespace std;

void User::interface() {}

string User::getAccount() {
    return this->account;
}

string User::getPassword() {
    return this->password;
}

bool User::getIsAdmin() {
    return this->isAdmin;
}

int User::getCheckedOutCount() {
    ifstream in;
    in.open("ReaderFile\\" + this->account + ".txt");
    if (!in) {
        cout << "User not found." << endl;
        return 0;
    }
    
    int count = 0;
    in >> count; //read the number of checked out books
    in.close();
    return count;
}




bool User::login() {

    string account;
    string correctPassword;

    //user enters account
    cout << "Please enter your username: " << endl;
    cin >> account;
    
    if (account == "admin") {
        correctPassword = "admin"; //admin correct password
    } else {
        ifstream in;
        in.open("ReaderFile\\" + account + ".txt");
        if (!in) {
            cout << "User not found." << endl;
            return 0;
        }
    
        in >> correctPassword; //read user password from the file
        in.close();
    }
    

    //user enters password
    string password;
    cout << "Please enter your password: " << endl;
    cin >> password;
    
    if (password == correctPassword) {
        this->account = account;
        this->password = password;
        if (account == "admin") {
            isAdmin = 1;
            return 1;
        } else {
            cout << "Login successful!" << endl;
            cout << "Welcome back, " << account << "!" << endl;
            isAdmin = 0;
            return 1;
        }
    }
    else {
        cout << "Incorrect password." << endl;
        return 0;
    }
}

bool User::registerUser() {
    //user enters account
    string account;
    cout << "Please set up your username: " << endl;
    cin >> account;
    ifstream in;
    in.open("ReaderFile\\" + account + ".txt");
    if (in || account == "admin") {
        cout << "Username already exists." << endl;
        return 0;
    }
    
    //user enters password
    string password;
    cout << "Please set up your password: " << endl;
    cin >> password;
    
    //create account
    this->account = account;
    this->password = password;
    ofstream out;
    out.open("ReaderFile\\" + account + ".txt");
    if (!out) {
        cout << "Unable to open the file!!!" << endl;
        return 0;
    }

    
    cout << "Account created!" << endl;
    out << password << endl;
    out.close();
    this->isAdmin = 0;
    return 1;
}



