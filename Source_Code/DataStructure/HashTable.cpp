#include <string>
#include "HashTable.h"
#include "../Classes/Book.h"

using namespace std;

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
    return stoi(key) % size; 
}

void HashTable::insert(Book* book, string key) {
    table[hashFunction(key)].push_back(book);
}

Book* HashTable::search(const string& type, const string& key) const {
    int index = hashFunction(key);
    for (auto book : table[index]) {
        if (type == "author" && book->getAuthor() == key) {
            return book;
        }
        if (type == "publisher" && book->getPublisher() == key) {
            return book;
        }
        if (type == "year" && to_string(book->getPublishedYear()) == key) {
            return book;
        }
    }
    return nullptr; 
}
