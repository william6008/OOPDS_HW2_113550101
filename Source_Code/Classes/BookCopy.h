#ifndef BOOKCOPY_H
#define BOOKCOPY_H

#include <string>
#include <ctime>
#include "Book.h"

using namespace std;

class BookCopy : public Book {
private:
    int ID;
    tm due_date;

public:
    BookCopy(string title, string author, string publisher, int published_year, int ID, tm due_date);
    friend class Library;
};

#endif 