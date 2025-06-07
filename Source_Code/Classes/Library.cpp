#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "library.h"
#include "Book.h"
#include "BookCopy.h"
#include "../DataStructure/HashTable.h"
#include "../Helper/Helper.h"

using namespace std;

//constructor
Library::Library() : titleSearch(1009), authorSearch(1009), publisherSearch(1009), yearSearch(1009) {
    load();
}

//system
void Library::load() {
    ifstream in;
    in.open("MyLibrary\\MyLibrary.txt");
    if (!in) {
        type("Unable to open the file!!!\n", 1);
        throw "Unable to open the file!!!";
    }

    string title;
    string author;
    string publisher;
    int published_year;
    int available;
    int lent;

    books.clear();

    for (int i = 0; getline(in, title, '|'); i++) {
        getline(in, author, '|');
        getline(in, publisher, '|');
        in >> published_year;
        in.ignore(1, '|');
        in >> available;
        in.ignore(1, '|');
        in >> lent;
        in.ignore(1, '\n');
        books.push_back(new Book(title, author, publisher, published_year, available, lent));
        titleSearch.insert(books.back(), books.back()->getTitle());
        authorSearch.insert(books.back(), books.back()->getAuthor());
        publisherSearch.insert(books.back(), books.back()->getPublisher());
        yearSearch.insert(books.back(), to_string(books.back()->getPublishedYear()));
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
            books.back()->addCopy(ID, due_date, books.back());
        }


    }
    in.close();
    return;
}

void Library::save() {
    ofstream out;
    out.open("MyLibrary\\MyLibrary.txt", ios::trunc);
    if (!out) {
        type("Unable to open the file!!!\n", 1);
        throw "Unable to open the file!!!";
    }

    for (auto& it : books) {
        out << it->title << "|" << it->author << "|" << it->publisher << "|" << it->published_year << "|" << it->available << "|" << it->lent;
        out << endl;
        for (auto& it2 : it->copies) {
            out << it2.ID << "|" << it2.due_date.tm_year << "|" << it2.due_date.tm_mon << "|" << it2.due_date.tm_mday;
            out << endl;
        }
    }
    out.close();
    return;
}

//both

void Library::displayBook() {
    clearScreen();
    cout << "| No. |      title      |      author      |     publisher     | published year | available copies |" << endl;
    delay(1);
    delay(1);
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (long long i = 0; i < beShown.size(); i++) {
        showSpace(to_string(i + 1), 5);
        showSpace(beShown[i]->getTitle(), 16);
        showSpace(beShown[i]->getAuthor(), 16);
        showSpace(beShown[i]->getPublisher(), 16);
        showSpace(to_string(beShown[i]->getPublishedYear()), 16);
        showSpace(to_string(beShown[i]->getAvailable()), 16);
        type("\n", 1);
        delay(1);
    }

}

void Library::search() {
    type("Search by: \n", 1);
    type("1. Title\n", 1);
    type("2. Author\n", 1);
    type("3. Publisher\n", 1);
    type("4. Published Year\n", 1);
    int op;
    cin >> op;
    if (cin.peek() == '\n') cin.ignore();
    switch (op) {
        case 1:
            searchByTitle();
            break;
        case 2:
            searchByAuthor();
            break;
        case 3:
            searchByPublisher();
            break;
        case 4:
            searchByYear();
            break;
        default:
            type("Invalid option!\n", 1);
    }
}

void Library::searchByTitle() {
    string title;
    type("Please enter the title of the book: \n", 1);
    getline(cin, title); 
    beShown = titleSearch.search("title", title);
    if (beShown.empty()) {
        type("No book found." + title + "\n", 1);
    } else {
        type("Books with title " + title + ": \n", 1);
        displayBook();
    }
}

void Library::searchByAuthor() {
    string author;
    type("Please enter the author of the book: \n", 1);
    getline(cin, author); 
    beShown = authorSearch.search("author", author);
    if (beShown.empty()) {
        type("No book found by author: " + author + "\n", 1);
    } else {
        type("Books by " + author + ": \n", 1);
        displayBook();
    }
}

void Library::searchByPublisher() {
    string publisher;
    type("Please enter the publisher of the book: \n", 1);
    getline(cin, publisher); 
    beShown = publisherSearch.search("publisher", publisher);
    if (beShown.empty()) {
        type("No book found by publisher " + publisher + "\n", 1);
    } else {
        type("Books published by " + publisher + ": \n", 1);
        displayBook();
    }
}

void Library::searchByYear() {
    string year;
    type("Please enter the published year of the book: \n", 1);
    getline(cin, year);
    beShown = yearSearch.search("year", year);
    if (beShown.empty()) {
        type("No book found published in year: " + year + "\n", 1);
    } else {
        type("Books published in " + year + ": \n", 1);
        displayBook();
    }
}

void Library::listAllBooks() {
    beShown = books;
    if (beShown.empty()) {
        type("No book found.\n", 1);
    } else {
        type("All books: \n", 1);
        displayBook();
    }
}



//admin


void Library::addBook() {
    string title;
    string author;
    string publisher;
    int published_year;
    int quantity;
    if (cin.peek() == '\n') cin.ignore();
    type("Please enter the title of the book: \n", 1); 
    inputCheck(&title);
    type("Please enter the author of the book: \n", 1);
    inputCheck(&author);
    type("Please enter the publisher of the book: \n", 1);
    inputCheck(&publisher);
    type("Please enter the published year of the book: \n", 1);
    cin >> published_year;
    type("Please enter the quantity of the book's copy: \n", 1);
    cin >> quantity;

    books.push_back(new Book(title, author, publisher, published_year, quantity, 0));
    titleSearch.insert(books.back(), books.back()->getTitle());
    authorSearch.insert(books.back(), books.back()->getAuthor());
    publisherSearch.insert(books.back(), books.back()->getPublisher());
    yearSearch.insert(books.back(), to_string(books.back()->getPublishedYear()));
    save();
}

void Library::removeCopy(int id, int quantity) {
    if (id < 0 || id >= beShown.size()) {
        type("Invalid book ID!\n", 1);
        return;
    }
    if (beShown[id]->getAvailable() < quantity || quantity <= 0) {
        type("Invalid quantity\n", 1);
        return;
    }

    beShown[id]->available -= quantity;
    return;
}

//reader





