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

public:
    BookCopy(int ID, tm due_date, Book* parentBook);
    friend class Library;
};

#endif 