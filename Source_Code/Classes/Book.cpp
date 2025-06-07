#include <iostream>
#include <string>
#include "Book.h"
#include "BookCopy.h"

using namespace std;

Book::Book(string title, string author, string publisher, int published_year, int available, int lent) {
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->published_year = published_year;
    this->available = available;
    this->lent = lent;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

string Book::getPublisher() const {
    return publisher;
}

int Book::getPublishedYear() const {
    return published_year;
}

int Book::getAvailable() const {
    return available;
}

int Book::getLent() const {
    return lent;
}



void Book::addCopy(int ID, tm due_date, Book* parentBook) {
    copies.push_back(BookCopy(ID, due_date, parentBook));
    available++;
    lent--;
}