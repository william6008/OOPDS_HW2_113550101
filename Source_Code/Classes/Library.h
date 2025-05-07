#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <ctime>
#include "Book.h"
#include "BookCopy.h"

using namespace std;

class Library {
private:
    vector<Book> books;
    vector<Book*> beShown;
    bool isAdmin;

public:
    //constructor
    Library(bool isAdmin);

    //system
    void load();
    void save();

    //admin
    void addBook();
    void removeCopy();
    
    //both
    
    void displayBook();

    void bookDetails(int No);


    void searchByTitle();
    void searchByAuthor();
    void searchByPublisher();
    void searchByYear();
    void listAllBooks();

    //reader
    void checkOutBook();
    void returnBook();
    
    void exit();

};

#endif 
