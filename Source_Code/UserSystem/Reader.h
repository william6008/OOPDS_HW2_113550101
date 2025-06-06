#ifndef READER_H
#define READER_H

#include <vector>
#include "User.h"
#include "../Classes/BookCopy.h"

using namespace std;


class Reader : public User {
private:
    vector<BookCopy> checkedOutBooks;
    int checkedOutCount;


public:
    Reader(User& user);
    int getCheckedOutCount();
    void interface() override;
    void load();
    void save();
};



#endif