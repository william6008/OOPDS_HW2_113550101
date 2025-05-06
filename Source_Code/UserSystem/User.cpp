#include<fstream>
#include<iostream>
#include<string>
#include "User.h"

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
    cout << "Please enter your username: " << endl;
    cin >> account;
    
    if (account == "admin") {
        correctPassword = "admin"; //admin correct password
    } else {
        ifstream in;
        in.open("..\\ReaderFile\\" + account + ".txt");
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
    in.open("..\\ReaderFile\\" + account + ".txt");
    if (in || account == "admin") {
        cout << "Username already exists." << endl;
        return 0;
    }
    
    //user enters password
    string password;
    cout << "Please set up your password: " << endl;
    cin >> password;
    
    //create account
    cout << "Account created!" << endl;
    this->account = account;
    this->password = password;
    ofstream out;
    out.open("File\\" + account + ".txt");
    out << password << endl;
    out.close();
    return 1;
}

void User::adminInterface() {
    cout << "Admin Interface" << endl;
    int op;
    while (op != 0) {
        cout << "1. Add Book" << endl;
        cout << "2. Remove Book" << endl;
        cout << "3. List All Books" << endl;
        cout << "0. Exit" << endl;
        cin >> op;
        switch (op) {
            case 1:
                //addBook();
                break;
            case 2:
                //removeBook();
                break;
            case 3:
                //listAllBooks();
                break;
            case 0:
                cout << "Exiting admin interface." << endl;
                break;
            default:
                cout << "Invalid option." << endl;
        }
    }

}

void User::readerInterface() {
    cout << "Welcome to the reader interface!" << endl;
}