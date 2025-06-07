#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <ctime>
#include "Book.h"
#include "BookCopy.h"
#include "../DataStructure/HashTable.h"

using namespace std;

class Library {
private:
    vector<Book*> books;
    HashTable titleSearch;
    HashTable authorSearch;
    HashTable publisherSearch;
    HashTable yearSearch;
    vector<Book*> beShown;

public:
    //constructor
    Library();
    //system
    void load();
    void save();

    //admin
    void addBook();
    void removeCopy(int id, int quantity);
    
    //both
    
    void displayBook();

    void search();
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
