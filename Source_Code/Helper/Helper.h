#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <ctime>
#include <set>
#include <thread>

using namespace std;

string input(const set<string>& expected, const string& error);

tm inputDate();

void showSpace(string str, int width = 16);

void inputCheck(string* target);

void clearScreen();

void type(const string& str, int delay = 5);

void delay(int seconds);

#endif