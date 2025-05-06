#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <iostream>
#include <string>
#include <ctime>
#include <set>

using namespace std;

string input(const set<string>& expected, const string& error);
tm inputDate();


#endif