#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>
#include <vector>
#include "../Classes/Book.h"

using namespace std;

class AVLNode {
friend class AVL;
private:
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;
    


public:
    Book book;
    AVLNode(const Book& book);
    ~AVLNode();



};

class AVL {
private:
    AVLNode* root;
    int getHeight(AVLNode* node);
    void updateHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    void destroy(AVLNode* node);

    
public:
    AVL();
    ~AVL();
    
    void insert(Book* book);
    Book* search(const string& title);

    



};

#endif