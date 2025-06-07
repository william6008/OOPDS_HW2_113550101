#include "BookCopy.h"

using namespace std;

BookCopy::BookCopy(int ID, tm due_date, Book* parentBook, string reader) {
    this->ID = ID;
    this->due_date = due_date;
    this->parentBook = parentBook;
    this->reader = reader;
}