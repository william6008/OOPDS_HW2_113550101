#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <ctime>
#include "../Classes/Book.h"
#include "../Classes/BookCopy.h"
using namespace std;

class User {
private:
    bool isAdmin; 
    string account;
    string password;
    int lentbooks = 0; 
    vector<BookCopy*> mybooks; 

public:
    string getAccount();
    string getPassword();
    int getPunishment();
    bool getIsAdmin();
    
    bool login();
    bool registerUser();


    

friend class Library;
};

#endif