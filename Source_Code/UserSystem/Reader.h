#ifndef READER_H
#define READER_H

#include "User.h"

using namespace std;

class Reader : public User {
public:
    Reader(User& user);
    void interface() override;
};



#endif