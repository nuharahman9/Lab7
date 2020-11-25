//
// Created by Nuha Rahman on 11/18/20.
//

#include <iostream>

#include "AVLTree.h"

using namespace std;

int menu() {
    int choice = 0;
    cout << endl;
    cout << "Enter menu choice: ";
    cout << endl;
    cout << "1. Insert" << endl;
    cout << "2. Print" << endl;
    cout << "3. Quit" << endl;
    cin >> choice;

    // fix buffer just in case non-numeric choice entered
    // also gets rid of newline character
    cin.clear();
    cin.ignore(256, '\n');
    return choice;
}

int main() {
    AVLTree tree;
    int choice = menu();

    while (choice != 3) {
        if (choice == 1) {
            string entry;
            cout << "Enter string to insert: ";
            getline(cin, entry);
            cout << endl;

            tree.insert(entry);
        } else if (choice == 2) {
            tree.printBalanceFactors();
        }
        // fix buffer just in case non-numeric choice entered
        choice = menu();
    }

    return 0;
}