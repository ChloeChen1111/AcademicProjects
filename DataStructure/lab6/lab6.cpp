// AUTHOR:   Shunuo Chen
// FILENAME: lab6.cpp
// DATE:     11/20/2022
// PURPOSE:  This program implement a hash table with hash function
// PROCESS:  Create a hash table, add key and value to the hash table, using
//           key to find values in the table, and check if the key in the table
// OUTPUT:   Prints the key in the table

#include <iostream>
#include "HashTable.h"
#include <string>

using namespace std;

void welcome();
// Prints welcome message

string checkFlag(bool);
// get the returned bool
// IN: bool
// MODIFY: convert bool to string
// OUT: true or false

void goodbye();
// Prints goodbye message

int main() {
    welcome(); //call the welcome function
    cout << "\nCreating a new HashTable with capacity 4093 and inserting \n"
            "4083 random key-value pairs with unique keys.. done.\n\n";
    //create an instance of the HashTable class
    HashTable *hashtable = new HashTable(4093);

    //insert 4083 random key-value pairs with unique keys to the hashtable
    for (int i = 1; i <= 4083; i ++) {
        hashtable->put(i, rand());
    }
    cout << "Inserting 10 additional key-values..\n";
    //call the put function to insert 10 more key and value pairs
    hashtable->put(1179, 120);
    hashtable->put(9702, 121);
    hashtable->put(7183, 122);
    hashtable->put(50184, 123);
    hashtable->put(4235, 124);
    hashtable->put(644, 125);
    hashtable->put(77, 126);
    hashtable->put(3077, 127);
    hashtable->put(23477, 128);
    hashtable->put(90777, 129);
    cout << "(1179 , 120)" << endl;
    cout << "(9702 , 121)" << endl;
    cout << "(7183 , 122)" << endl;
    cout << "(50184 , 123)" << endl;
    cout << "(4235 , 124)" << endl;
    cout << "(644 , 125)" << endl;
    cout << "(77 , 126)" << endl;
    cout << "(3077 , 127)" << endl;
    cout << "(23477 , 128)" << endl;
    cout << "(90777 , 129)" << endl;
    cout << endl;

    //call the contains functions to check if key contains in the hastable
    cout << "Testing contains.." << endl;
    cout << "contains(50184): "
        << checkFlag(hashtable->contains(50184)) << endl;
    cout << "contains(   77): "
        << checkFlag(hashtable->contains(   77)) << endl;
    cout << "contains(    0): "
        << checkFlag(hashtable->contains(    0)) << endl;
    cout << "contains(   -1): "
        << checkFlag(hashtable->contains(   -1)) << endl;

    //call the get functions to get the value with the key in the hastable
    cout << "\nTesting get..." << endl;
    cout << "test get(50184): " << hashtable->get(50184) <<endl;
    cout << "test get(   77): " << hashtable->get(77) <<endl;
    cout << "test get(    0): " << hashtable->get(0) <<endl;
    cout << "test get(   -1): " << hashtable->get(-1) <<endl;

    //call the goodbye function to display goodbye message
    goodbye();
    return 0;
}
//To display welcome message
void welcome() {
    cout << "\nWelcome to the HashTable testing program." << endl;
}

//To display goodbye message
void goodbye() {
    cout << "\nThanks for using the HashTable testing "
            "program. Goodbye." << endl;
}

//Convert boolean to string
//Accepting boolean flag
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