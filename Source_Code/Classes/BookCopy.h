#ifndef BOOKCOPY_H
#define BOOKCOPY_H

#include <string>
#include <ctime>

using namespace std;

class Book; 

class BookCopy {
private:
    int ID;
    tm due_date;
    int parentBookIndex;

public:
    BookCopy(int ID, tm due_date, int parentBookIndex);
    friend class Library;
    friend class Reader;
};

#endif 