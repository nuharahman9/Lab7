//
// Created by Nuha Rahman on 11/18/20.
//


#include"AVLTree.h"
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;


void AVLTree::insert(const string &str) {
    if (root == 0) {
        root = new Node(str);
        return;
    }

    Node* vParent = search(str, root);
    Node* child = new Node(str);
    child->parent = vParent;

    if (str < vParent->data) {
        vParent->left = child;
    }
    else if (str > vParent->data) {
        vParent->right = child;
    }
    else {
        return;
    }

    Node* temp = findUnbalancedNode(child);
    if (temp) {
        rotate(temp);
    }
}

Node* AVLTree::search(const string &str, Node* curr) const {
    if (curr->data == str) {
        return curr;
    }
    if (str < curr->data) {
        if (curr->left) {
            return search(str, curr->left);
        }
        else {
            return curr;
        }
    }
    else {
        if (curr->right) {
            return search(str, curr->right);
        }
        return curr;
    }
}

int AVLTree::balanceFactor(Node* curr) {
    if (curr == 0) {
        return 0;
    }
    return height(curr->left) - height(curr->right);
}

void AVLTree::printBalanceFactors()  {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node* curr)  {
    if(curr) {
        printBalanceFactors(curr->left);
        cout << curr->data << "(" << balanceFactor(curr) << "), ";
        printBalanceFactors(curr->right);
    }
}
int AVLTree::height(Node* curr) const {
    if (curr == 0) {
        return -1;
    }
    int left = height(curr->left);
    int right = height(curr->right);
    if (left > right) {
        return left + 1;
    }
    else {
        return right + 1;
    }
}

void AVLTree::visualizeTree(const string& outputFilename) const {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error" << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename =
            outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream& outFS, Node* node) const {
    if (node) {
        if (node->left) {
            visualizeTree(outFS, node->left);
            outFS << node->data << " -> " << node->left->data << ";" << endl;
        }
        if (node->right) {
            visualizeTree(outFS, node->right);
            outFS << node->data << " -> " << node->right->data << ";" << endl;
        }
    }
}





Node* AVLTree::rotateRight(Node* node) {
    Node* leftRightChild = node->left->right;
    if(node->parent != NULL) {
        if(node->parent->left == node) {
            node->parent->left = node->left;
            if(node->left != NULL) {
                node->left->parent = node->parent;
            }
        }
        else if (node->parent->right == node) {
            node->parent->right = node->left;
            if(node->left != NULL) {
                node->left->parent = node->parent;
            }
        }
    }
    else {
        root = node->left;
        root->parent = NULL;
    }
    node->left->right = node;
    if(node != nullptr) {
        node->parent = node->left;
    }
    node->left = leftRightChild;
    if(leftRightChild != nullptr) {
        leftRightChild->parent = node;
    }
    return node->parent;
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* rightLeftChild = node->right->left;
    if (node->parent != 0) {
        if (node->parent->right == node) {
            node->parent->right = node->right;
            if (node->right != 0) {
                node->right->parent = node->parent;
            }
        }
        else if (node->parent->left == node) {
            node->parent->left = node->right;
            if (node->right != 0) {
                node->right->parent = node->parent;
            }
        }
    }
    else {
        root = node->right;
        root->parent = 0;
    }

    node->right->left = node;
    if (node != 0) {
        node->parent = node->right;
    }
    node->right = rightLeftChild;
    if (rightLeftChild) {
        rightLeftChild->parent = node;
    }
    return node->parent;
}

Node* AVLTree::findUnbalancedNode(Node* curr) {
    if (curr == 0) {
        return 0;
    }

    int bFactor = balanceFactor(curr);
    if (bFactor == -2 || bFactor == 2) {
        return curr;
    }
    else {
        return findUnbalancedNode(curr->parent);
    }
}


void AVLTree::rotate(Node* node) {
    int bFactor = balanceFactor(node);
    int childBFactor1 = balanceFactor(node->left);
    int childBFactor2 = balanceFactor(node->right);
    if (bFactor == 2) {
        if (childBFactor1 == 1 || childBFactor2 == 1) {
            rotateRight(node);
        }
        else {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    else {
        if (childBFactor1 == -1 || childBFactor2 == -1) {
            rotateLeft(node);
        }
        else {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}