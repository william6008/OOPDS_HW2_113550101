#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "../Classes/Book.h"
#include "../Classes/BookCopy.h"
using namespace std;

class User {
private:
    bool isAdmin; 
    string account;
    string password;
    vector<BookCopy*> mybooks; 
    int punishment; 
    int lentbooks;
public:
    string getAccount();
    string getPassword();
    int getPunishment();
    bool getIsAdmin();
    
    bool login();
    bool registerUser();

    void user_save();

    

friend class Library;
};

#endif