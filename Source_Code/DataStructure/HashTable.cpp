#include <string>
#include "HashTable.h"
#include "../Classes/Book.h"

using namespace std;

int convert (const string& str) {
    int result = 0;
    for (auto it : str) {
        result += it;
    }
    return result;
}

HashTable::HashTable(int size) : size(size) {
    table.resize(size);
}

HashTable::~HashTable() {
    for (auto& it : table) {
        for (auto it2 : it) {
            delete it2;
        }
    }
}

int HashTable::hashFunction(const string& key) const {
    return convert(key) % size; 
}

void HashTable::insert(Book* book, string key) {
    table[hashFunction(key)].push_back(book);
}

string tolower(const string str) {
    string result = str;
    for (char& c : result) {
        if ('A' <= c && c <= 'Z') {
            c = tolower(c);
        }
    }
    return result;
}

vector<Book*> HashTable::search(const string& type, const string& key) const {
    vector<Book*> results;
    string key_lw = tolower(key);
    int index = hashFunction(key);
    for (auto it : table[index]) {
        if ((type == "title" && tolower(it->getTitle()) == key_lw) ||
            (type == "author" && tolower(it->getAuthor()) == key_lw) ||
            (type == "publisher" && tolower(it->getPublisher()) == key_lw) ||
            (type == "year" && to_string(it->getPublishedYear()) == key)) {
            results.push_back(it);
        }


    }
    return results;
}
