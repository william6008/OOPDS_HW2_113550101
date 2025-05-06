#include <iostream>
#include <string>
#include <set>
#include <ctime>
#include "InputSystem.h"

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
        cout << input << " is not allowed. " << error << endl;
    }
}

tm inputDate() {
    tm date = {};
    int year, month, day;

    while (cin >> year >> month >> day) {
        int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) days[1] = 29; 

        if (year <= 0 || month < 1 || month > 12 || day < 1 || day > days[month - 1]) {
            cout << "Invalid date. Please enter a valid date (yyyy mm dd): " << endl;
            continue;
        }
        break;
    }

    date.tm_year = year - 1900;
    date.tm_mon = month - 1;
    date.tm_mday = day;

    return date;
}

