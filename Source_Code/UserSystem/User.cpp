#include<fstream>
#include<iostream>
#include<string>
#include "../Classes/library.h"
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
        correctPassword = "admin"; //admin correct password
    } else {
        ifstream in;
        in.open("ReaderFile\\" + account + ".txt");
        if (!in) {
            type("User not found.\n", 1);
            return 0;
        }
    
        in >> correctPassword; //read user password from the file
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
            return 1;
        }
    }
    else {
        type("Incorrect password.\n", 1);
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
    if (!out) // Check if the file opened successfully
    {
        type("Unable to open the file!!!\n", 1);
        return 0;
    }
    else  // File opened successfully
    {
        /* code */
    }
    
    type("Account created!\n", 1);
    out << password << endl;
    out.close();
    this->isAdmin = 0;
    return 1;
}

void User::adminInterface() {
    type("Welcome to the admin Interface\n", 1);
    Library library;
    int op = -1;
    while (op != 0) {
        type("1. Add Book\n", 1);
        type("2. Remove Book\n", 1);
        type("3. List All Books\n", 1);
        type("4. Search Books\n", 1);
        type("0. Exit\n", 1);
        cin >> op;
        switch (op) {
            case 1:
                library.addBook();
                break;
            case 2:
                //removeBook();
                break;
            case 3:
                library.listAllBooks();
                break;
            case 4:
                library.search();
                break;
            case 0:
                type("Exiting admin interface.\n", 1);
                break;
            default:
                type("Invalid option.\n", 1);
        }
    }

}

void User::readerInterface() {
    int op = -1;
    while (op != 0) {
        type("1. Search Books\n", 1);
        type("2. Check Out Book\n", 1);
        type("3. Return Book\n", 1);
        type("4. List All Books\n", 1);
        type("0. Exit\n", 1);
        cin >> op;
        switch (op) {
            case 1:
                //searchByYear();
                break;
            case 2:
                //searchByAuthor();
                break;
            case 3:
                //searchByTitle();
                break;
            case 4:
                //searchByPublisher();
                break;
            case 5:
                //checkOutBook();
                break;
            case 6:
                //returnBook();
                break;
            case 7:
                //listAllBooks();
                break;
            case 0:
                type("Exiting reader interface.\n", 1);
                break;
            default:
                type("Invalid option.\n", 1);
        }
    }
}