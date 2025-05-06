#include <iostream>
#include <fstream>
#include <string>
#include "library.h"

using namespace std;

void Library::load() {
    ifstream in;
    in.open("..\\MyLibrary\\MyLibrary.txt");
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
            books.back().addCopy(ID, due_date);
        }


    }
    in.close();
    return;
}

void Library::save() {
    ofstream out;
    out.open("..\\MyLibrary\\MyLibrary.txt", ios::trunc);
    if (!out) {
        cout << "Unable to open the file!!!" << endl;
        throw "Unable to open the file!!!";
    }

    for (int i = 0; i < books.size(); i++) {
        out << books[i].title << "|" << books[i].author << "|" << books[i].publisher << "|" << books[i].published_year << "|" << books[i].available << "|" << books[i].lent;
        out << endl;
        for (int j = 0; j < books[i].copies.size(); j++) {
            out << "|" << books[i].copies[j].ID << "|" << books[i].copies[j].due_date.tm_year << "|" << books[i].copies[j].due_date.tm_mon << "|" << books[i].copies[j].due_date.tm_mday;
        }
        out << endl;
    }
    out.close();
    return;
}

