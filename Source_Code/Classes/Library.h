#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <ctime>
#include "Book.h"
#include "BookCopy.h"
#include "../UserSystem/User.h"

using namespace std;

class Library {
private:
    vector<Book> books;
    vector<Book*> beShown;
    User user;

public:
    //constructor
    Library(User& user);

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
    BookCopy* checkOutBook(int No);
    void returnBook();
    void showOverdueBooks();
    
    void exit();

};

#endif 
