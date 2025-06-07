#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <iostream>
#include "../Classes/Book.h"

using namespace std;

class HashTable {
private:
    vector<vector<Book*>> table;
    int size;
    int hashFunction(const string& key) const;

public:
    HashTable(int size);
    ~HashTable();

    void insert(Book* book, string key);
    vector<Book*> search(const string& type, const string& key) const;


};

#endif