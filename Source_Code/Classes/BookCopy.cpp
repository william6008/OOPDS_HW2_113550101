
#include "BookCopy.h"

using namespace std;

BookCopy::BookCopy(int ID, tm due_date, Book* parentBook) {
    this->ID = ID;
    this->due_date = due_date;
    this->parentBook = parentBook;
}