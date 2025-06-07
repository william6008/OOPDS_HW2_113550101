#include <iostream>
#include <fstream>
#include <string>
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
        cout << "Unable to open the file!!!" << endl;
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
        cout << "Unable to open the file!!!" << endl;
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
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (long long i = 0; i < beShown.size(); i++) {
        showSpace(to_string(i + 1), 5);
        showSpace(beShown[i]->getTitle(), 16);
        showSpace(beShown[i]->getAuthor(), 16);
        showSpace(beShown[i]->getPublisher(), 16);
        showSpace(to_string(beShown[i]->getPublishedYear()), 16);
        showSpace(to_string(beShown[i]->getAvailable()), 16);
        cout << endl;
    }

}

void Library::search() {
    cout << "Search by: " << endl;
    cout << "1. Title" << endl;
    cout << "2. Author" << endl;
    cout << "3. Publisher" << endl;
    cout << "4. Published Year" << endl;
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
            cout << "Invalid option!" << endl;
    }
}

void Library::searchByTitle() {
    string title;
    cout << "Please enter the title of the book: " << endl;
    getline(cin, title); 
    beShown = titleSearch.search("title", title);
    if (beShown.empty()) {
        cout << "No book found." << title << endl;
    } else {
        displayBook();
    }
}

void Library::searchByAuthor() {
    string author;
    cout << "Please enter the author of the book: " << endl;
    getline(cin, author); 
    beShown = authorSearch.search("author", author);
    if (beShown.empty()) {
        cout << "No book found by author: " << author << endl;
    } else {
        displayBook();
    }
}

void Library::searchByPublisher() {
    string publisher;
    cout << "Please enter the publisher of the book: " << endl;
    getline(cin, publisher); 
    beShown = publisherSearch.search("publisher", publisher);
    if (beShown.empty()) {
        cout << "No book found by publisher: " << publisher << endl;
    } else {
        displayBook();
    }
}

void Library::searchByYear() {
    string year;
    cout << "Please enter the published year of the book: " << endl;
    getline(cin, year);
    beShown = yearSearch.search("year", year);
    if (beShown.empty()) {
        cout << "No book found published in year: " << year << endl;
    } else {
        displayBook();
    }
}

void Library::listAllBooks() {
    beShown = books;
    if (beShown.empty()) {
        cout << "No book found." << endl;
    } else {
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

    books.push_back(new Book(title, author, publisher, published_year, quantity, 0));
    titleSearch.insert(books.back(), books.back()->getTitle());
    authorSearch.insert(books.back(), books.back()->getAuthor());
    publisherSearch.insert(books.back(), books.back()->getPublisher());
    yearSearch.insert(books.back(), to_string(books.back()->getPublishedYear()));
    save();
}

void Library::removeCopy(int id, int quantity) {
    if (id < 0 || id >= beShown.size()) {
        cout << "Invalid book ID!" << endl;
        return;
    }
    if (beShown[id]->getAvailable() < quantity || quantity <= 0) {
        cout << "Invalid quantity" << endl;
        return;
    }

    beShown[id]->available -= quantity;
    return;
}

//reader





