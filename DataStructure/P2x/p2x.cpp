// AUTHOR:   Shunuo Chen
// FILENAME: p2x.cpp
// DATE:     10/29/2022
// PURPOSE:  This program implement a BST template class.
// INPUT:    User input of integers.dat and strings.dat. The integers and
//           strings add into the binary research tree
// PROCESS:  Read the two file and insert information into the binary research
//           tree. Then verify contains function, remove function, getLevel,
//           getAncestors function.
// OUTPUT:   Prints the integers and strings in the binary search tree, also
//           display the width of the tree, as well as the level order

#include <iostream>
#include "BSTx.h"
#include <string>
#include <fstream>


using namespace std;

void displayIntTree(BST<int> &intTree);
// display the content in the integer tree
// IN: The instance of BST<T> class (BST<int> intTree)
// MODIFY: none
// OUT: the tested function in the BST<T> class


void readIntFile(BST<int> &);
// read the integer file
// IN: file with integers
// MODIFY: none
// OUT: none


string checkFlag(bool);
// get the returned bool
// IN: bool
// MODIFY: convert bool to string
// OUT: true or false

int main() {

    BST<int> intTree; //create an instance of BST<int>
    displayIntTree(intTree); //display information in the int tree
    return 0;
}

void displayIntTree(BST<int> &intTree) {
    cout << "******************************" << endl <<
         "* INTEGER BINARY SEARCH TREE *" << endl <<
         "******************************" << endl << endl;

    cout << "** CREATE BST **" << endl
         //call the size function to get the quantities of nodes in the ineTree
         << "# of nodes:  " << intTree.size() << endl
         //call the empty function to check if the tree is empty
         << "BST empty?   " << checkFlag(intTree.empty()) << endl << endl;
    readIntFile(intTree); //call the readIntFile function to read the input file
    cout <<endl;
    cout << "The width of the tree: " << intTree.getWidth() <<endl;
    cout << "Level Order of the tree: " << intTree.getLevelOrder() << endl;

}

string checkFlag(bool flag) {
    if (flag) {
        // when the variable flag is true, return string "true"
        return "true";
    }
    else {
        // when the variable flag is false, return string "false"
        return "false";
    }
}

void readIntFile(BST<int> & intTree) {
    //create a variable to hold the filename
    string intFile;
    //create an instance of the ifstream,
    ifstream inFile;

    //prompt the user to enter the file
    cout << "Enter integer file: ";
    getline(cin, intFile);
    cout << endl << "** TEST INSERT **" << endl;
    string line;
    cout << "Inserting in this order: ";
    inFile.open(intFile);
    //verify the file is opened
    if (inFile.is_open()) {
        //insert elements in the file to the BST
        while (getline(inFile, line)) {
            int number = stoi(line); //convert string to integer
            cout << number << " ";
            intTree.insert(number);
        }
        cout << endl;
    }
}
