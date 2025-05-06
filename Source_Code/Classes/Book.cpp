#include <iostream>
#include <string>
#include "Book.h"

using namespace std;

Book::Book(string title, string author, string publisher, int published_year, int available, int lent) {
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->published_year = published_year;
    this->available = available;
    this->lent = lent;
}

void Book::addCopy(int ID, tm due_date) {
    BookCopy newCopy(title, author, publisher, published_year, ID, due_date);
    copies.push_back(newCopy);
    available++;
    lent--;
}