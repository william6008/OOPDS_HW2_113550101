#include <iostream>
#include <string>
#include "Book.h"
#include "BookCopy.h"

using namespace std;

Book::Book(int index, string title, string author, string publisher, int published_year, int available, int lent, int popularity) {
    this->index = index;
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->published_year = published_year;
    this->available = available;
    this->lent = lent;
    this->popularity = popularity;
}


