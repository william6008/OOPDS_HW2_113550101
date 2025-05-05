#ifndef BOOKCOPY_H
#define BOOKCOPY_H

#include <string>
#include <ctime>
#include "Book.h"

using namespace std;

class BookCopy : public Book {
private:
    int ID;
    bool isLent;
    tm due_date;
};

#endif 