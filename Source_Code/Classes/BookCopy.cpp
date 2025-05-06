
#include "BookCopy.h"
#include "Book.h"

using namespace std;

BookCopy::BookCopy(string title, string author, string publisher, int published_year, int ID, tm due_date) : Book(title, author, publisher, published_year, 0, 0), ID(ID), due_date(due_date) {
    this->ID = ID;
    this->due_date = due_date;
}