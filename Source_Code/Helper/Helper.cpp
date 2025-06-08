#include <iostream>
#include <string>
#include <set>
#include <ctime>
#include "Helper.h"
#include "../Classes/Book.h"
#include "../Classes/BookCopy.h"
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


void showSpace(string str, int width) {
    int len = str.length();
    string copy;
    cout << " ";
    if (len > width) {
        copy = str.substr(0, width - 3) + "...";
        len = width;
    } else {
        copy = str;
    }

    for (int i = 0; i < (width - len) / 2; i++) {
        cout << " ";
    }

    cout << copy;

    for (int i = 0; i < (width - len) / 2 + ((width - len) % 2); i++) {
        cout << " ";
    }
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
    this_thread::sleep_for(chrono::milliseconds(seconds));
}

void sortByTitle(vector<Book*>& books) {
    vector<Book*> left, right;
    if (books.size() <= 1) return;
    left = vector<Book*>(books.begin(), books.begin() + books.size() / 2);
    right = vector<Book*>(books.begin() + books.size() / 2, books.end());
    sortByTitle(left);
    sortByTitle(right);
    books.clear();
    while (!left.empty() && !right.empty()) {
        if (left.front()->getTitle() < right.front()->getTitle()) {
            books.push_back(left.front());
            left.erase(left.begin());
        } else {
            books.push_back(right.front());
            right.erase(right.begin());
        }
    }
    while (!left.empty()) {
        books.insert(books.end(), left.begin(), left.end());
        left.clear();
    }
    while (!right.empty()) {
        books.insert(books.end(), right.begin(), right.end());
        right.clear();
    }

}

void sortByTitle (vector<BookCopy*>& copies) {
    vector<BookCopy*> left, right;
    if (copies.size() <= 1) return;
    left = vector<BookCopy*>(copies.begin(), copies.begin() + copies.size() / 2);
    right = vector<BookCopy*>(copies.begin() + copies.size() / 2, copies.end());
    sortByTitle(left);
    sortByTitle(right);
    copies.clear();
    while (!left.empty() && !right.empty()) {
        if (left.front()->getParentBook()->getTitle() < right.front()->getParentBook()->getTitle()) {
            copies.push_back(left.front());
            left.erase(left.begin());
        } else {
            copies.push_back(right.front());
            right.erase(right.begin());
        }
    }
    while (!left.empty()) {
        copies.insert(copies.end(), left.begin(), left.end());
        left.clear();
    }
    while (!right.empty()) {
        copies.insert(copies.end(), right.begin(), right.end());
        right.clear();
    }
}