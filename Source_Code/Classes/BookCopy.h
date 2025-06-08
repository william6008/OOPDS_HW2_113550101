#ifndef BOOKCOPY_H
#define BOOKCOPY_H

#include <string>
#include <ctime>

using namespace std;

class Book; 

class BookCopy {
private:
    tm due_date;
    Book* parentBook;
    string reader;

public:
    BookCopy(tm due_date, Book* parentBook, string reader);
    Book* getParentBook() const;
    bool operator== (const BookCopy& other) const;
    friend class Library;
};

#endif 