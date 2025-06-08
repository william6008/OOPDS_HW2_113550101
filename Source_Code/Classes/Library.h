#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <ctime>
#include <functional>
#include "../UserSystem/User.h"
#include "Book.h"
#include "BookCopy.h"
#include "../DataStructure/HashTable.h"

using namespace std;

class Library {
private:
    User user;
    vector<Book*> books;
    HashTable titleSearch;
    HashTable authorSearch;
    HashTable publisherSearch;
    HashTable yearSearch;
    vector<Book*> beShown;
    function<void()> lastsearch;

public:
    //constructor
    Library(User& user);
    //system
    void load();
    void save();

    //admin
    void addBook();
    void changeQuantity();
    
    //both
    
    void displayBook();

    void search();
    void searchByTitle(string title);
    void searchByAuthor(string author);
    void searchByPublisher(string publisher);
    void searchByYear(string year);
    void listAllBooks(string useless = "");

    //reader
    void showMyBooks();
    void checkOutBook();
    void returnBook();
    

};

#endif 

