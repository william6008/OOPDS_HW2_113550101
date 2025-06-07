#include <iostream>
#include <string>
#include <set>
#include <ctime>
#include "Helper.h"
#include <thread>
#include <chrono>

using namespace std;

string input(const set<string>& expected, const string& error) {
    string input;
    while (true) {
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, input);
        // to lowercase
        for (char& c : input) {
            if ('A' <= c && c <= 'Z') {
                c = tolower(c);
            }
        }
        if (expected.count(input)) {
            return input;
        }
        type(input + " is not allowed. " + error + "\n", 1);
    }
}

tm inputDate() {
    tm date = {};
    int year, month, day;

    while (cin >> year >> month >> day) {
        int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) days[1] = 29; 

        if (year <= 0 || month < 1 || month > 12 || day < 1 || day > days[month - 1]) {
            type("Invalid date. Please enter a valid date (yyyy mm dd): \n", 1);
            continue;
        }
        break;
    }

    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    return date;
}

void showSpace(string str, int width) {
    int len = str.length();
    string copy;
    cout << " ";
    if (len > width - 2) {
        copy = str.substr(0, width - 5) + "...";
        len = width - 2;
    } else {
        copy = str;
    }

    for (int i = 0; i < (width - len) / 2; i++) {
        cout << " ";
    }

    cout << copy;

    for (int i = 0; i < (width - len) / 2 + (len % 2); i++) {
        cout << " ";
    }
    cout << " ";
}

void inputCheck(string* target) {
    bool valid = 0;
    while (!valid) {
        getline(cin, *target);
        valid = 1;
        for (auto it : *target) {
            if (it == '|') {
                type("'|' is not allowed.\n", 1);
                valid = 0;
                break;
            }
        }
    }
}

void clearScreen() {
    type("\033[2J\033[1;1H", 1); 
}

void type(const string& str, int delay) {
    for (auto it : str) {
        cout << it;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

void delay(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}