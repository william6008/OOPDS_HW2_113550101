#include <iostream>
#include <fstream>
#include <string>
#include "library.h"

using namespace std;

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

void showSpace(string& str) {
    int len = str.length();
    string copy;

    if (len > 14) {
        copy = str.substr(0, 11) + "...";
        len = 14;
    } else {
        copy = str;
    }

    for (int i = 0; i < (16 - len) / 2; i++) {
        cout << " ";
    }

    cout << copy;

    for (int i = 0; i < (16 - len) / 2 + (len % 2); i++) {
        cout << " ";
    }
}

void Library::displayBook() {
    cout << "" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    
    // 顯示每本書的資訊
    int i = 0;  // 用來顯示書本的編號
    for (auto it = beShown.begin(); it != beShown.end(); it++, i++) {
        // 顯示書本編號
        showSpace(to_string(i));
        
        // 顯示書本名稱
        showSpace((*it)->getName());

        // 顯示書本分類
        showSpace((*it)->getCategory());

        // 顯示到期時間（如果有的話）
        if ((*it)->getDueTime().tm_year != -1) {
            string dueDate = to_string((*it)->getDueTime().tm_year + 1900) + "/" + 
                             to_string((*it)->getDueTime().tm_mon + 1) + "/" + 
                             to_string((*it)->getDueTime().tm_mday);
            showSpace(dueDate);
        } else {
            showSpace("-");
        }

        // 顯示是否完成
        if ((*it)->getCompleted()) {
            showSpace("Yes");
        } else {
            showSpace("No");
        }

        cout << endl;
    }

    cout << "--------------------------------------------------------------------------------" << endl;
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





