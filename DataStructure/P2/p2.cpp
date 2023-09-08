// AUTHOR:   Shunuo Chen
// FILENAME: p2.cpp
// DATE:     10/24/2022
// PURPOSE:  This program implement a BST template class.
// INPUT:    User input of integers.dat and strings.dat. The integers and
//           strings add into the binary research tree
// PROCESS:  Read the two file and insert information into the binary research
//           tree. Then verify contains function, remove function, getLevel,
//           getAncestors function.
// OUTPUT:   Prints the integers and strings in the binary search tree, also
//           display the size, leaf nodes, height, and specific element at
//           specific level, as well as ancestors

#include <iostream>
#include "BST.h"
#include <string>
#include <fstream>


using namespace std;

void displayWelcomeMessage();
// display the welcome message
// IN: none
// MODIFY: none
// OUT: the welcome message

void displayGoodbyeMessage();
// display the goodbye message
// IN: none
// MODIFY: none
// OUT: the goodbye message

void displayIntTree(BST<int> &intTree);
// display the content in the integer tree
// IN: The instance of BST<T> class (BST<int> intTree)
// MODIFY: none
// OUT: the tested function in the BST<T> class

void displayStringTree(BST<string> &stringTree);
// display the content in the string tree
// IN: The instance of BST<T> class (BST<string> stringTree)
// MODIFY: none
// OUT: the tested function in the BST<T> class

void readIntFile(BST<int> &);
// read the integer file
// IN: file with integers
// MODIFY: none
// OUT: none

void readStringFile(BST<string> &);
// read the string file
// IN: file with strings
// MODIFY: none
// OUT: none

string checkFlag(bool);
// get the returned bool
// IN: bool
// MODIFY: convert bool to string
// OUT: true or false

int main() {
    displayWelcomeMessage(); //call the display welcome message function
    BST<int> intTree; //create an instance of BST<int>
    BST<string> stringTree; //create an instance of BST<string>
    displayIntTree(intTree); //display information in the int tree
    displayStringTree(stringTree); //display information in the string tree
    displayGoodbyeMessage();//call the goodbye message
    return 0;
}

void displayWelcomeMessage() {
    cout << "Welcome to the BST "
            "implementation program! " << endl << endl;
}

void displayGoodbyeMessage () {
    cout << endl << endl << "Goodbye!" << endl;
}

void displayIntTree(BST<int> &intTree) {
    cout << "******************************" << endl <<
         "* INTEGER BINARY SEARCH TREE *" << endl <<
         "******************************" << endl << endl;

    cout << "** CREATE BST **" << endl
         //call the size function to get the quantities of nodes in the ineTree
         << "# of nodes:  " << intTree.size() << endl
         //call the getLeafCount to get the number of leaf nodes
         << "# of leaves: " << intTree.getLeafCount() << endl
         //call the getHeight to get the height of the tree
         << "BST height:  " << intTree.getHeight() << endl
         //call the empty function to check if the tree is empty
         << "BST empty?   " << checkFlag(intTree.empty()) << endl << endl;
    readIntFile(intTree); //call the readIntFile function to read the input file
    //call the size function to get the quantities of nodes in the ineTree
    cout << "# of nodes:  " << intTree.size() << endl;
    //call the getLeafCount to get the number of leaf nodes
    cout << "# of leaves: " << intTree.getLeafCount() << endl;
    //call the getHeight to get the height of the tree
    cout << "tree height: " << intTree.getHeight() << endl;
    //call the empty function to check if the tree is empty
    cout << "tree empty?  " << checkFlag(intTree.empty()) << endl << endl;

    cout << "** TEST TRAVERSALS **" << endl;
    //display the tree in a preorder traversal
    cout << "pre-order:  " << intTree.getPreOrderTraversal() << endl;
    //display the tree in an inorder traversal
    cout << "in-order:   " << intTree.getInOrderTraversal() << endl;
    //display the tree in a postorder traversal
    cout << "post-order: " << intTree.getPostOrderTraversal() << endl << endl;

    cout << "** TEST LEVEL & ANCESTORS **" << endl;
    //create an array to hold the elements in the tree
    int testArray1[7] = { 40, 20, 10, 30, 60, 50, 70 };
    for (int i = 0; i < 7; i++ ) {
        //get the level of a specific node
        cout << "level(" << testArray1[i] << "): " <<
        intTree.getLevel(testArray1[i]) << ", ";
        cout << "ancestors(" << testArray1[i] << "): " <<
        intTree.getAncestors(testArray1[i]) << endl;
    }
    cout << endl;
    cout << "** TEST CONTAINS **" << endl;
    //create an array to hold elements want to check if containing in the tree
    int testArray2[8] = {20, 40, 10, 70, 99, -2, 59, 43};
    //check if a specific element in the tree
    for (int i = 0; i < 8; i++ ) {
        cout << "contains(" << testArray2[i] << "): " <<
             checkFlag(intTree.contains(testArray2[i])) << endl;
    }
    cout << endl;

    cout << "** TEST REMOVE **" << endl;
    //remove the element held in the testArray2
    cout << "Removing in this order: ";
    for (int i = 0; i < 8; i++ ) {
        cout << testArray2[i] << " ";
        intTree.remove(testArray2[i]);
    }
    cout << endl;
    //check the size after removing
    cout << "# of nodes:  " << intTree.size() << endl;
    //check the leaves after removing
    cout << "# of leaves: " << intTree.getLeafCount() << endl;
    //check the tree height after removing
    cout << "tree height: " << intTree.getHeight() << endl;
    //check if the tree is empty after removing
    cout << "tree empty?  " << checkFlag(intTree.empty()) << endl;
    //display the BST in pre-order
    cout << "pre-order:  " << intTree.getPreOrderTraversal() << endl;
    //display the BST in in-order
    cout << "in-order:   " << intTree.getInOrderTraversal() << endl;
    //display the BST in post-order
    cout << "post-order: " << intTree.getPostOrderTraversal() << endl << endl;

    cout << "** TEST INSERT (again) **" << endl;
    //create another array to hold elements needed to insert in the BST
    int testArray3[8] = {20, 40, 10, 70, 99, -2, 59, 43};
    cout << "Inserting in this order: ";
    for (int i = 0; i < 8; i++ ) {
        cout << testArray3[i] << " ";
        //Insert elements in the array into the BST
        intTree.insert(testArray3[i]);
    }
        cout << endl;
        //display the size of the BST
        cout << "# of nodes:  " << intTree.size() << endl;
        //display the leaves of the BST
        cout << "# of leaves: " << intTree.getLeafCount() << endl;
        //display the height of the BST
        cout << "tree height: " << intTree.getHeight() << endl;
        //check if the BST is empty
        cout << "tree empty?  " << checkFlag(intTree.empty()) << endl;
        //display the BST in pre-order
        cout << "pre-order:  " << intTree.getPreOrderTraversal() << endl;
        //display the BST in in-order
        cout << "in-order:   " << intTree.getInOrderTraversal() << endl;
        //display the BST in post-order
        cout << "post-order: " << intTree.getPostOrderTraversal() << endl << endl;
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

void displayStringTree(BST<string> &stringTree) {
    //display the empty BST
    cout << endl << "********************" << endl <<
         "* test string BST  *" << endl <<
         "********************" << endl << endl;

    cout << "# of nodes:  " << stringTree.size() << endl
         << "# of leaves: " << stringTree.getLeafCount() << endl
         << "BST height:  " << stringTree.getHeight() << endl
         << "BST empty?   " << checkFlag(stringTree.empty()) << endl << endl;
    //call the read file function to read the input file
    readStringFile(stringTree);
    //display the size, leaves, height in the BST after inserting the tree
    cout << "# of nodes:  " << stringTree.size() << endl;
    cout << "# of leaves: " << stringTree.getLeafCount() << endl;
    cout << "tree height: " << stringTree.getHeight() << endl;
    cout << "tree empty?  " << checkFlag(stringTree.empty()) << endl << endl;

    //display the tree in 3 different ways
    cout << "** TEST TRAVERSALS **" << endl;
    cout << "pre-order:  " << stringTree.getPreOrderTraversal() << endl;
    cout << "in-order:   " << stringTree.getInOrderTraversal() << endl;
    cout << "post-order: " << stringTree.getPostOrderTraversal() << endl << endl;

    //display the levels and ancestors of specific elements
    cout << "** TEST LEVEL & ANCESTORS **" << endl;
    string testArray1[7] = {"mary", "gene", "bea", "jen", "sue", "pat", "uma"};
    for (int i = 0; i < 7; i++ ) {
        cout << "level(" << testArray1[i] << "): " <<
             stringTree.getLevel(testArray1[i]) << ", ";
        cout << "ancestors(" << testArray1[i] << "): " <<
             stringTree.getAncestors(testArray1[i]) << endl;
    }
    cout << endl;

    //check if the BST contain the specific information
    cout << "** TEST CONTAINS **" << endl;
    string testArray2[8] = {"gene", "mary", "bea", "uma", "yan", "amy", "ron", "opal"};
    for (int i = 0; i < 8; i++ ) {
        cout << "contains(" << testArray2[i] << "): " <<
             checkFlag(stringTree.contains(testArray2[i])) << endl;
    }
    cout << endl;
    //remove elements held in the array from the BST
    cout << "** TEST REMOVE **" << endl;
    cout << "Removing in this order: ";
    for (int i = 0; i < 8; i++ ) {
        cout << testArray2[i] << " ";
        stringTree.remove(testArray2[i]);
    }
    cout << endl;
    //display the size, leaves, height, if empty after removing from the tree
    cout << "# of nodes:  " << stringTree.size() << endl;
    cout << "# of leaves: " << stringTree.getLeafCount() << endl;
    cout << "tree height: " << stringTree.getHeight() << endl;
    cout << "tree empty?  " << checkFlag(stringTree.empty()) << endl;
    //display the tree in 3 different ways
    cout << "pre-order:  " << stringTree.getPreOrderTraversal() << endl;
    cout << "in-order:   " << stringTree.getInOrderTraversal() << endl;
    cout << "post-order: " << stringTree.getPostOrderTraversal() << endl << endl;

    //insert element held in the array into the BST
    cout << "** TEST INSERT (again) **" << endl;
    string testArray3[8] = {"gene", "mary", "bea", "uma", "yan", "amy", "ron", "opal" };
    cout << "Inserting in this order: ";
    for (int i = 0; i < 8; i++ ) {
        cout << testArray3[i] << " ";
        stringTree.insert(testArray3[i]);
    }
    cout << endl;
    //display the size, leaves, height, if empty after inserting the tree
    cout << "# of nodes:  " << stringTree.size() << endl;
    cout << "# of leaves: " << stringTree.getLeafCount() << endl;
    cout << "tree height: " << stringTree.getHeight() << endl;
    cout << "tree empty?  " << checkFlag(stringTree.empty()) << endl;
    cout << "pre-order:  " << stringTree.getPreOrderTraversal() << endl;
    cout << "in-order:   " << stringTree.getInOrderTraversal() << endl;
    cout << "post-order: " << stringTree.getPostOrderTraversal() << endl << endl;
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

void readStringFile(BST<string> & stringTree) {
    //create an instance of the ifstream,
    ifstream inFile;
    //create a variable to hold the filename
    string stringFile;
    string line;
    //prompt the user to enter the file
    cout << "Enter string file: ";

    getline(cin, stringFile);
    //Open the file
    inFile.open(stringFile);
    cout << endl << "** TEST INSERT **" << endl;
    cout << "Inserting in this order: ";
    //verify the file is opened
    if(inFile.is_open()) {
        //insert elements in the file to the BST
        while (getline(inFile, line)) {
            cout <<line << " ";
            stringTree.insert(line);
        }
        cout << endl;
    }
}
