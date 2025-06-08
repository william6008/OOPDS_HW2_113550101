#include "BookCopy.h"

using namespace std;

BookCopy::BookCopy(tm due_date, Book* parentBook, string reader) {
    this->due_date = due_date;
    this->parentBook = parentBook;
    this->reader = reader;
}

bool BookCopy::operator==(const BookCopy& other) const {
    tm this_due_date_copy = this->due_date;
    tm other_due_date_copy = other.due_date;
    return (mktime(&this_due_date_copy) == mktime(&other_due_date_copy) &&
            this->reader == other.reader &&
            this->parentBook == other.parentBook);
    }

Book* BookCopy::getParentBook() const {
    return parentBook;
}