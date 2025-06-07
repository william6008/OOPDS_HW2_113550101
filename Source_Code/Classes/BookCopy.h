#ifndef BOOKCOPY_H
#define BOOKCOPY_H

#include <string>
#include <ctime>

using namespace std;

class Book; 

class BookCopy {
private:
    int ID;
    tm due_date;
    Book* parentBook;
    string reader;

public:
    BookCopy(int ID, tm due_date, Book* parentBook, string reader);
    friend class Library;
};

#endif 