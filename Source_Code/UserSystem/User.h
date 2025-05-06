#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
private:
    bool isAdmin; 
    string account;
    string password;

public:
    string getAccount();
    string getPassword();
    bool getIsAdmin();
    
    bool login();
    bool registerUser();

    void adminInterface();
    void readerInterface();
};

#endif