#ifndef BOOK_H
#define BOOK_H


#include <vector>
#include <string>
#include <ctime>
#include "bookCopy.h"

using namespace std;

class Book {
private:
    vector<BookCopy> copies;
    static int available;
    static int lent;

protected:
    string title;
    int published_year;
    string author;
    string publisher;

public:
    


};

#endif 