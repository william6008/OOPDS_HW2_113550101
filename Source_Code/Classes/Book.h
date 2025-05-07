#ifndef BOOK_H
#define BOOK_H


#include <vector>
#include <string>
#include <ctime>

using namespace std;

class BookCopy;

class Book {
private:
    vector<BookCopy> copies;
    int available;
    int lent;
    int index;
    int popularity;

protected:
    string title;
    string author;
    string publisher;
    int published_year;
    

public:
    Book(int index
        , string title
        , string author
        , string publisher
        , int published_year
        , int available
        , int lent
        , int popularity
    );

    void addCopy(int ID, tm due_date, int parentBookIndex);;
    

    friend class Library;
};

#endif 