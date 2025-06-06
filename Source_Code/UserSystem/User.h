#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    bool isAdmin; 
    string account;
    string password;

public:
    string getAccount();
    string getPassword();
    int getCheckedOutCount();
    bool getIsAdmin();
    
    bool login();
    bool registerUser();

    virtual void interface();
};

#endif