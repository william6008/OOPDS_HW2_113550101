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

public:
    //system
    void load(const string& filename);
    void save(const string& filename);

    //admin
    void addBook(const Book& book);
    void userAddBook();
    void userRemoveBook();
    
    //reader
    void searchByYear();
    void searchByAuthor();
    void searchByTitle();
    void searchByPublisher();
    void checkOutBook();
    void returnBook();
    void listAllBooks();
    void exit();

};

#endif 
