#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <conio.h>
#include "library.h"
#include "Book.h"
#include "BookCopy.h"
#include "../UserSystem/User.h"
#include "../DataStructure/HashTable.h"
#include "../Helper/Helper.h"

using namespace std;

//constructor
Library::Library(User& user) : titleSearch(1009)
                                , authorSearch(1009)   
                                , publisherSearch(1009)
                                , yearSearch(1009)
                                , user(user) {
    load();
    lastsearch = nullptr;
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
            string reader;
            tm due_date = { 0 };
            in >> due_date.tm_year;
            in.ignore(1, '|');
            in >> due_date.tm_mon;
            in.ignore(1, '|');
            in >> due_date.tm_mday;
            in.ignore(1, '|');
            in >> reader;
            in.ignore(1, '\n');
            books.back()->copies.push_back(new BookCopy(due_date, books.back(), reader));
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
        out << it->title << "|" << it->author << "|" << it->publisher 
        << "|" << it->published_year << "|" << it->available << "|" << it->lent;
        out << endl;
        for (auto& it2 : it->copies) {
            out << it2->due_date.tm_year << "|" 
            << it2->due_date.tm_mon << "|" << it2->due_date.tm_mday << "|" << it2->reader;
            out << endl;
        }
    }
    out.close();
    return;
}

//both

void Library::displayBook() {
    sortByTitle(beShown);
    cout << "| No. |      title      |      author      |     publisher     | published year | available copies |" << endl;
    delay(1);
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    delay(1);
    for (long long i = 0; i < beShown.size(); i++) {
        showSpace(to_string(i + 1), 5);
        showSpace(beShown[i]->getTitle(), 17);
        showSpace(beShown[i]->getAuthor(), 18);
        showSpace(beShown[i]->getPublisher(), 19);
        showSpace(to_string(beShown[i]->getPublishedYear()), 16);
        showSpace(to_string(beShown[i]->getAvailable()), 18);
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
    string target;
    cin >> op;
    if (cin.peek() == '\n') cin.ignore();
    switch (op) {
        case 1:
            type("Please enter the title of the book: \n", 1);
            getline(cin, target); 
            searchByTitle(target);
            lastsearch = bind(&Library::searchByTitle, this, target);
            break;
        case 2:
            type("Please enter the author of the book: \n", 1);
            getline(cin, target);
            searchByAuthor(target);
            lastsearch = bind(&Library::searchByAuthor, this, target);
            break;
        case 3:
            type("Please enter the publisher of the book: \n", 1);
            getline(cin, target); 
            searchByPublisher(target);
            lastsearch = bind(&Library::searchByPublisher, this, target);
            break;
        case 4:
            type("Please enter the published year of the book: \n", 1);
            getline(cin, target);
            searchByYear(target);
            lastsearch = bind(&Library::searchByYear, this, target);
            break;
        default:
            type("Invalid option!\n", 1);
            delay(30);
            clearScreen();
            if (lastsearch) lastsearch();
            return;
    }
}

void Library::searchByTitle(string title) {
    beShown = titleSearch.search("title", title);
    clearScreen();
    if (beShown.empty()) {
        type("No book found." + title + "\n", 1);
    } else {
        type("Books with title " + title + ": \n", 1);
        displayBook();
    }
}

void Library::searchByAuthor(string author) {    
    beShown = authorSearch.search("author", author);
    clearScreen();
    if (beShown.empty()) {
        type("No book found by author: " + author + "\n", 1);
    } else {
        type("Books by " + author + ": \n", 1);
        displayBook();
    }
    lastsearch = bind(&Library::searchByAuthor, this, author);
    return;
}

void Library::searchByPublisher(string publisher) {
    beShown = publisherSearch.search("publisher", publisher);
    clearScreen();
    if (beShown.empty()) {
        type("No book found by publisher " + publisher + "\n", 1);
    } else {
        type("Books published by " + publisher + ": \n", 1);
        displayBook();
    }
    lastsearch = bind(&Library::searchByPublisher, this, publisher);
    return;
}

void Library::searchByYear(string year) {
    beShown = yearSearch.search("year", year);
    clearScreen();
    if (beShown.empty()) {
        type("No book found published in year: " + year + "\n", 1);
    } else {
        type("Books published in " + year + ": \n", 1);
        displayBook();
    }
    lastsearch = bind(&Library::searchByYear, this, year);
    return;
}

void Library::listAllBooks(string useless) {
    clearScreen();
    beShown = books;
    if (beShown.empty()) {
        type("No book found.\n", 1);
    } else {
        type("All books: \n", 1);
        displayBook();
    }
    lastsearch = bind(&Library::listAllBooks, this, useless);
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
    type("Book added successfully!\n", 1);
    delay(10);
    clearScreen();
    if (lastsearch) {
        lastsearch();
    }
    save();
}

void Library::changeQuantity() {
    type("Please enter the index of the book: \n", 1);
    int index;
    cin >> index;
    if (index < 1 || index > books.size()) {
        type("Invalid index!\n", 1);
        lastsearch();
        return;
    }
    index--;
    type("Current quantity: " + to_string(books[index]->getAvailable()) + "\n", 1);
    type("Please enter the new quantity: \n", 1);
    int new_quantity;
    cin >> new_quantity;
    if (new_quantity < 0) {
        type("Quantity cannot be negative!\n", 1);
        lastsearch();
        return;
    }
    if (new_quantity < books[index]->getLent()) {
        type("New quantity shouldn't less than lent copies!\n", 1);
        lastsearch();
        return;
    }
    
    books[index]->available = new_quantity - books[index]->lent;
    save();
    type("Quantity changed successfully!\n", 1);
    lastsearch();
    return;

}

//reader
void Library::showMyBooks() {
    delay(10);
    clearScreen();
    if (user.mybooks.empty()) {
        type("You have no books checked out.\n", 1);
        return;
    }
    type("My books:\n", 1);
    int overdue = 0;
    cout << "| No. |      title      |      author      |     publisher     | published year |    due date    |" << endl;
    delay(1);
    cout << "--------------------------------------------------------------------------------------------------" << endl;
    delay(1);
    time_t now = time(0);

    for (long long i = 0; i < user.mybooks.size(); i++) {
        tm due_date = user.mybooks[i]->due_date;
        if (mktime(&due_date) < now) {
            cout << "\033[31m"; //red words
            overdue++;
        }
        showSpace(to_string(i + 1), 5);
        showSpace(user.mybooks[i]->parentBook->getTitle(), 17);
        showSpace(user.mybooks[i]->parentBook->getAuthor(), 18);
        showSpace(user.mybooks[i]->parentBook->getPublisher(), 19);
        showSpace(to_string(user.mybooks[i]->parentBook->getPublishedYear()), 16);
        showSpace(to_string(user.mybooks[i]->due_date.tm_year + 1900) + "/" + 
                to_string(user.mybooks[i]->due_date.tm_mon + 1) + "/" + 
                to_string(user.mybooks[i]->due_date.tm_mday), 16);
        type("\n", 1);
        delay(1);
        cout << "\033[0m"; //reset color
    }
    if (overdue > 0) {
        cout << "\033[31m"; //red words
        type("You have " + to_string(overdue) + " overdue book(s).\n", 1);
        type("Please return them as soon as possible\n", 1);
        cout << "\033[0m"; //reset color
    }
    return;
    
}


void Library::checkOutBook() {
    if (user.mybooks.size() >= 10) {
        type("You have checked out 10 books, please return some first\n", 1);
        lastsearch();
        return;
    }
    type("Please enter the index of the book: \n", 1);
    int index;
    cin >> index;
    if (index < 1 || index > beShown.size()) {
        type("Invalid index!\n", 1);
        lastsearch();
        return;
    }
    index--;
    if (beShown[index]->getAvailable() <= 0) {
        type("No available copies for this book now.\n", 1);
        tm soon = {0};
        for (auto& it : beShown[index]->copies) {
            if (mktime(&it->due_date) > mktime(&soon)) {
                soon = it->due_date;
            }
        }
        type("You may lend this book at: " + to_string(soon.tm_year + 1900) 
        + "/" + to_string(soon.tm_mon + 1) + "/" + to_string(soon.tm_mday) + "\n", 1);
        type("Type any key to continue\n", 1);
        _getch(); 
        lastsearch();
        return;
    }
    time_t now = time(0);
    tm due_date = *localtime(&now);
    due_date.tm_mon += 1;  
    beShown[index]->copies.push_back(new BookCopy(due_date, beShown[index], user.account));
    user.mybooks.push_back(beShown[index]->copies.back());
    
    beShown[index]->available--;
    beShown[index]->lent++;

    user.lentbooks++;
    
    save();
    type("Book checked out successfully!\n", 1);
    type("Press any key to continue\n", 1);
    _getch(); 
    lastsearch();
}

void Library::returnBook() {
    if (user.mybooks.empty()) {
        type("You have no books checked out.\n", 1);
        return;
    }
    type("Please enter the index of the book you want to return: \n", 1);
    int index;
    cin >> index;
    if (index < 1 || index > user.mybooks.size()) {
        type("Invalid index!\n", 1);
        showMyBooks();
        return;
    }
    index--;
    BookCopy* target = user.mybooks[index];
    target->parentBook->available++;
    target->parentBook->lent--;
    type("Book returned successfully!\n", 1);
    
    auto& del = target->parentBook->copies;
    auto it = find(del.begin(), del.end(), target);
    if (it != del.end()) del.erase(it);
    user.mybooks.erase(user.mybooks.begin() + index);
    user.lentbooks--;
    target = nullptr;
    delete target;
    save();
    type("Press any key to continue\n", 1);
    _getch();
    
    showMyBooks();
    return;

}



