#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "Library.h"
#include "Book.h"
#include "BookCopy.h"

using namespace std;

//constructor
Library::Library(bool isAdmin): isAdmin(isAdmin){}


//system
void Library::load() {
    ifstream in;
    in.open("MyLibrary\\MyLibrary.txt");
    if (!in) {
        cout << "Unable to open the file!!!" << endl;
        throw "Unable to open the file!!!";
    }

    string title;
    string author;
    string publisher;
    int published_year;
    int available;
    int lent;


    for (int i = 0; getline(in, title, '|'); i++) {
        getline(in, author, '|');
        getline(in, publisher, '|');
        in >> published_year;
        in.ignore(1, '|');
        in >> available;
        in.ignore(1, '|');
        in >> lent;
        in.ignore(1, '\n');
        books.push_back(Book(title, author, publisher, published_year, available, lent));
        for (int j = 0; j < lent; j++) {
            int ID;
            tm due_date = { 0 };
            in >> ID;
            in.ignore(1, '|');
            in >> due_date.tm_year;
            in.ignore(1, '|');
            in >> due_date.tm_mon;
            in.ignore(1, '|');
            in >> due_date.tm_mday;
            in.ignore(1, '\n');
            books.back().addCopy(ID, due_date, &books.back());
        }


    }
    in.close();
    return;
}

void Library::save() {
    ofstream out;
    out.open("MyLibrary\\MyLibrary.txt", ios::trunc);
    if (!out) {
        cout << "Unable to open the file!!!" << endl;
        throw "Unable to open the file!!!";
    }

    for (auto& it : books) {
        out << it.title << "|" << it.author << "|" << it.publisher << "|" << it.published_year << "|" << it.available << "|" << it.lent;
        out << endl;
        for (auto& it2 : it.copies) {
            out << it2.ID << "|" << it2.due_date.tm_year << "|" << it2.due_date.tm_mon << "|" << it2.due_date.tm_mday;
            out << endl;
        }
    }
    out.close();
    return;
}

//both

void showSpace(int allowLenth, string& str) {
    int len = str.length();
    string copy;

    if (len > allowLenth) {
        copy = str.substr(0, allowLenth - 3) + "...";
        len = allowLenth;
    } else {
        copy = str;
    }

    for (int i = 0; i < (allowLenth + 2 - len) / 2; i++) {
        cout << " ";
    }

    cout << copy;

    for (int i = 0; i < (allowLenth + 2 - len) / 2 + (len % 2); i++) {
        cout << " ";
    }
}

void Library::displayBook() {
   
    cout << "|  ID  |        Title        |       Author       |" << endl;
    cout << "---------------------------------------------------" << endl;
    for (int i = 0; i < sizeof(beShown); i++) {
        showSpace(6, to_string(i));
        
        showSpace(21, beShown[i]->title);

        showSpace(20, beShown[i]->author);
        cout << endl;
    }

    cout << "---------------------------------------------------" << endl;

    cout << "Choose a book number to proceed." << endl;
    cout << "Enter 0 to go back." << endl;

    int choice;
    cin >> choice;
    if (choice == 0) {
        return;
    } else if (choice > 0 && choice <= beShown.size()) {
        bookDetails(choice - 1);
    } else {
        cout << "Invalid choice. Please try again." << endl;
    } 
}

void Library::bookDetails(int No) {
    cout << "Title: " << beShown[No]->title << endl;
    cout << "Author: " << beShown[No]->author << endl;
    cout << "Publisher: " << beShown[No]->publisher << endl;
    cout << "Published Year: " << beShown[No]->published_year << endl;
    cout << "Available: " << beShown[No]->available << endl;
    cout << "Lent:" << beShown[No]->lent << endl;
    cout << endl;

    if (isAdmin) {
        cout << "1. Add copies" << endl;
        cout << "2. Remove copies" << endl;
        cout << "3. Go back" << endl;
        string choice;
        while (cin >> choice) {
            if (choice == "1") {
                addBook();
                break;
            } else if (choice == "2") {
                removeCopy();
                break;
            } else if (choice == "3") {
                break;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } else {
        cout << "1. Check out" << endl;
        cout << "2. Go back" << endl;
        string choice;
        while (cin >> choice) {
            if (choice == "1") {
                checkOutBook();
                break;
            } else if (choice == "2") {
                break;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
    
}







//admin
void inputCheck (string* target) {
    bool valid = 0;
    while (!valid) {
        getline(cin, *target);
        valid = 1;
        for (auto it : *target) {
            if (it == '|') {
                cout << "'|' is not allowed." << endl;
                valid = 0;
                break;
            }
        }
    }
}

void Library::addBook() {
    string title;
    string author;
    string publisher;
    int published_year;
    int quantity;
    if (cin.peek() == '\n') cin.ignore();
    cout << "Please enter the title of the book: " << endl; 
    inputCheck(&title);
    cout << "Please enter the author of the book: " << endl;
    inputCheck(&author);
    cout << "Please enter the publisher of the book: " << endl;
    inputCheck(&publisher);
    cout << "Please enter the published year of the book: " << endl;
    cin >> published_year;
    cout << "Please enter the quantity of the book's copy: " << endl;
    cin >> quantity;

    books.push_back(Book(title, author, publisher, published_year, quantity, 0));
    save();
}





