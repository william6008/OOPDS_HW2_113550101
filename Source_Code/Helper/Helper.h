#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <ctime>
#include <set>
#include <thread>
#include "../Classes/Book.h"
#include "../Classes/BookCopy.h"

using namespace std;

string input(const set<string>& expected, const string& error);

tm inputDate();

void showSpace(string str, int width = 16);

void inputCheck(string* target);

void clearScreen();

void type(const string& str, int delay = 5);

void delay(int seconds);

void sortByTitle(vector<Book*>& books);

#endif