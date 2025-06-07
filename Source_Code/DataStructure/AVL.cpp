#include <iostream>
#include <string>
#include "AVL.h"
#include "../Classes/Book.h"

using namespace std;

//--------------------------------------------AVLNode--------------------------------------------
AVLNode::AVLNode(const Book& book) : book(book), left(nullptr), right(nullptr), height(1) {
    key = stoi(book.getTitle()); 
}

AVLNode::~AVLNode() {
    delete left;
    delete right;
}

AVL::AVL() : root(nullptr) {}

void AVL::destroy(AVLNode* node) {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }
    return;
}
AVL::~AVL() {
    destroy(root);
}

int AVL::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

void AVL::updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

int AVL::getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLNode* AVL::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLNode* AVL::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

void AVL::insert(Book* book) {
    AVLNode* newNode = new AVLNode(*book);
    if (!root) {
        root = newNode;
        return;
    }

    AVLNode* current = root;
    AVLNode* parent = nullptr;

    while (current) {
        parent = current;
        if (newNode->key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (newNode->key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    updateHeight(parent);

    while (parent) {
        int balance = getBalance(parent);
        if (balance > 1 && newNode->key < parent->left->key) {
            parent = rotateRight(parent);
        } else if (balance < -1 && newNode->key > parent->right->key) {
            parent = rotateLeft(parent);
        } else if (balance > 1 && newNode->key > parent->left->key) {
            parent->left = rotateLeft(parent->left);
            parent = rotateRight(parent);
        } else if (balance < -1 && newNode->key < parent->right->key) {
            parent->right = rotateRight(parent->right);
            parent = rotateLeft(parent);
        }
        
        updateHeight(parent);
        if (parent == root) {
            root = parent;
            break;
        }
        parent = parent == root ? nullptr : (parent == root->left ? root : root->right);
    }
}

Book* AVL::search(const string& title) {
    if (!root) return nullptr;

    AVLNode* current = root;
    int key = stoi(title); 

    while (current) {
        if (key == current->key) {
            return &current->book;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return nullptr; 
}




