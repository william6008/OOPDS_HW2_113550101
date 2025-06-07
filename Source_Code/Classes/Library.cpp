#include <iostream>
#include <fstream>
#include <string>
#include <thread>
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
            int ID;
            tm due_date = { 0 };
            in >> ID;
            in.ignore(1, '|');
            in >> due_date.tm_year;
            in.ignore(1, '|');
            in >> due_date.tm_mon;
            in.ignore(1, '|');
            in >> due_date.tm_mday;
            in.ignore(1, '|');
            in >> reader;
            in.ignore(1, '\n');
            books.back()->addCopy(ID, due_date, books.back(), reader);
            if (reader == user.account) user.mybooks.push_back(&books.back()->copies.back());
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
            out << it2.ID << "|" << it2.due_date.tm_year << "|" 
            << it2.due_date.tm_mon << "|" << it2.due_date.tm_mday << "|" << it2.reader;
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
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    delay(1);
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
    }
}

void Library::searchByTitle(string title) {
    beShown = titleSearch.search("title", title);
    if (beShown.empty()) {
        type("No book found." + title + "\n", 1);
    } else {
        type("Books with title " + title + ": \n", 1);
        displayBook();
    }
}

void Library::searchByAuthor(string author) {    
    beShown = authorSearch.search("author", author);
    if (beShown.empty()) {
        type("No book found by author: " + author + "\n", 1);
    } else {
        type("Books by " + author + ": \n", 1);
        displayBook();
    }
}

void Library::searchByPublisher(string publisher) {
    beShown = publisherSearch.search("publisher", publisher);
    if (beShown.empty()) {
        type("No book found by publisher " + publisher + "\n", 1);
    } else {
        type("Books published by " + publisher + ": \n", 1);
        displayBook();
    }
}

void Library::searchByYear(string year) {
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
    type("Book added successfully!\n", 1);
    save();
}

void Library::changeQuantity() {
    type("Please enter the index of the book: \n", 1);
    int index;
    cin >> index;
    if (index < 1 || index > books.size()) {
        type("Invalid index!\n", 1);
        return;
    }
    index--;
    type("Current quantity: " + to_string(books[index]->getAvailable()) + "\n", 1);
    type("Please enter the new quantity: \n", 1);
    int new_quantity;
    cin >> new_quantity;
    if (new_quantity < 0) {
        type("Quantity cannot be negative!\n", 1);
        return;
    }
    if (new_quantity < books[index]->getAvailable()) {
        type("New quantity shouldn't less than available copies!\n", 1);
        return;
    }
    
    books[index]->available = new_quantity - books[index]->lent;
    save();
    type("Quantity changed successfully!\n", 1);
    return;

}

//reader
void Library::showMyBooks() {
    if (user.mybooks.empty()) {
        type("You have no books checked out.\n", 1);
        return;
    }
    int overdue = 0;
    clearScreen();
    cout << "| No. |      title      |      author      |     publisher     | published year | due date |" << endl;
    delay(1);
    cout << "--------------------------------------------------------------------------------------------" << endl;
    delay(1);
    time_t now = time(0);

    for (long long i = 0; i < user.mybooks.size(); i++) {
        tm due_date = user.mybooks[i]->due_date;
        if (mktime(&due_date) < now) {
            cout << "\033[31m"; //red words
            overdue++;
        }
        showSpace(to_string(i + 1), 5);
        showSpace(user.mybooks[i]->parentBook->getTitle(), 16);
        showSpace(user.mybooks[i]->parentBook->getAuthor(), 16);
        showSpace(user.mybooks[i]->parentBook->getPublisher(), 16);
        showSpace(to_string(user.mybooks[i]->parentBook->getPublishedYear()), 16);
        showSpace(to_string(user.mybooks[i]->due_date.tm_year + 1900) + "/" + to_string(user.mybooks[i]->due_date.tm_mon + 1) + "/" + to_string(user.mybooks[i]->due_date.tm_mday), 16);
        type("\n", 1);
        delay(1);
        cout << "\033[0m"; //reset color
    }
    if (overdue > 0) {
        type("You have " + to_string(overdue) + " overdue book(s).\n", 1);
        type("Please return them as soon as possible\n", 1);
    }
    return;
    
}


void Library::checkOutBook() {
    if (user.mybooks.size() >= 10) {
        type("You have checked out 10 books, please return some first\n", 1);
        return;
    }
    if (user.getPunishment() > 0) {
        type("You have a punishment of " + to_string(user.getPunishment()) + " days. You cannot check out books.\n", 1);
        return;
    }
    type("Please enter the index of the book: \n", 1);
    int index;
    cin >> index;
    if (index < 1 || index > beShown.size()) {
        type("Invalid index!\n", 1);
        return;
    }
    index--;
    if (beShown[index]->getAvailable() <= 0) {
        type("No available copies for this book now.\n", 1);
        tm soon = {0};
        for (auto& it : beShown[index]->copies) {
            if (mktime(&it.due_date) > mktime(&soon)) {
                soon = it.due_date;
            }
        }
        type("You may lend this book at: " + to_string(soon.tm_year + 1900) + "/" + to_string(soon.tm_mon + 1) + "/" + to_string(soon.tm_mday) + "\n", 1);

        return;
    }
    
    time_t now = time(0);
    tm due_date = *localtime(&now);
    due_date.tm_mon += 1; 
    
    int ID = beShown[index]->copies.size() + 1; 
    beShown[index]->addCopy(ID, due_date, beShown[index], user.getAccount());
    user.mybooks.push_back(&beShown[index]->copies.back());
    
    beShown[index]->available--;
    beShown[index]->lent++;

    user.lentbooks++;
    
    save();
    
    type("Book checked out successfully!\n", 1);

    showMyBooks();
}

void Library::returnBook() {
    type("Please enter the index of the book you want to return: \n", 1);
    int index;
    cin >> index;
    if (index < 1 || index > user.mybooks.size()) {
        type("Invalid index!\n", 1);
        return;
    }
    index--;
    BookCopy* target = user.mybooks[index];
    target->parentBook->available++;
    target->parentBook->lent--;
    target->parentBook->copies.erase(target->parentBook->copies.begin() + (target->ID - 1)); //remove the copy from the book's copies
    user.mybooks.erase(user.mybooks.begin() + index);
    user.lentbooks--;
    save();
    type("Book returned successfully!\n", 1);
    showMyBooks();
    return;

}



