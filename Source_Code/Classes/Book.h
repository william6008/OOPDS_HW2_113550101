#ifndef BOOK_H
#define BOOK_H


#include <vector>
#include <string>
#include <ctime>
#include "BookCopy.h"

using namespace std;

class BookCopy;

class Book {
private:
    vector<BookCopy*> copies;
    int available;
    int lent;
    string title;
    string author;
    string publisher;
    int published_year;
    

public:
    Book(string title, string author, string publisher
        , int published_year, int available, int lent);

    string getTitle() const;
    string getAuthor() const;
    string getPublisher() const;
    int getPublishedYear() const;
    int getAvailable() const;
    int getLent() const;

    friend class Library;
};

#endif 