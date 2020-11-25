//
// Created by Nuha Rahman on 11/18/20.
//

#include <iostream>
#include <string>

#ifndef _AVLTREE_H
#define _AVLTREE_H

using namespace std;

typedef struct Node {
    string data;
    unsigned int count;  // Increment if the same data is inserted.
    Node* left;
    Node* right;
    Node* parent;
    Node(const string &data)
            : data(data), count(1), left(nullptr), right(nullptr), parent(nullptr) {}
} Node;

class AVLTree {
public:
    void insert(const string& str);
    int balanceFactor(Node*) const;
    void printBalanceFactors();
    void visualizeTree(const string& str) const;

private:
    int balanceFactor(Node* );
    void rotate(Node* );
    int height(Node* ) const;
    Node* findUnbalancedNode(Node*);
    Node* doubleLeftRotate(Node* &);
    Node* doubleRightRotate(Node* &);
    Node* rotateLeft(Node* );
    Node* rotateRight(Node* );
    void printBalanceFactors(Node* ) ;
    void visualizeTree(ofstream& outFS, Node* node) const;
    Node *search(const string &, Node*) const;
    Node* root = 0;
};




#endif //_AVLTREE_H
