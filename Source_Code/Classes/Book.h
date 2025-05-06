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
    int available;
    int lent;

protected:
    string title;
    string author;
    string publisher;
    int published_year;
    

public:
    Book(string title, string author, string publisher, int published_year, int available, int lent);

    void lendBook(int ID, tm due_date);
    void returnBook(int ID);
    void addCopy(int ID, tm due_date);
    

    friend class Library;
};

#endif 