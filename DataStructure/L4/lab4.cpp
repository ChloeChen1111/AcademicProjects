// AUTHOR:   Shunuo Chen
// FILENAME: L4.cpp
// DATE:     10/20/2022
// PURPOSE:  This program take elements in the int array and double array to
//           store in the linkedlist, then display information in the list
// INPUT:    The context from the input file from
// PROCESS:  Create object of the template linkedlist class, and append elements
//           in the array to the linkedlist
// OUTPUT:   Print out all elements in the list and display the last negative
//           number in the list
#include <iostream>
#include <sstream>
#include "LinkedList.h"

using namespace std;

void displayFirstObject();
// display int elements in the linkedList
// IN: elements stored in the array
// MODIFY: none
// OUT: elements of the list and last negative number in the list

void displaySecondObject();
// display double elements in the linkedList
// IN: elements stored in the array
// MODIFY: none
// OUT: elements of the list and last negative number in the list

int main() {
    displayFirstObject();
    displaySecondObject();
    return 0;
}

void displayFirstObject() {

    //create an object of the LinkedList class
    LinkedList<int> *intList = new LinkedList<int>;

    int const SIZE = 7; //The size of the array
    int intArray[SIZE] = {3, -2, 5, 12, -2, -4, 5};
    //append element to the linkedlist
    for (int i = 0; i < SIZE; i++) {
        intList->append(intArray[i]);
    }
    //display elements in the linkedlist
    cout << "Linked list values: ";
    cout << intList->to_string();
    //display the last element in the list
    cout << "Last negative number: ";
    cout << intList->getLastNegative() << endl;
}

void displaySecondObject() {

    //create an object of the LinkedList class
    LinkedList<double>* doubleList = new LinkedList<double>;

    int const SIZE = 7; //The size of the array
    double doubleArray[SIZE] =
            {-3.2, 2.14, -5.7,
             -12.01,-2.99, 4.6, 5.2};
    //append element to the LinkedList
    for(int i = 0; i < SIZE; i++) {
        doubleList->append(doubleArray[i]);
    }
    //display elements in the LinkedList
    cout << "Linked list values: ";
    cout << doubleList->to_string();

    //display the last element in the list
    cout << "Last negative number: ";
    cout << doubleList->getLastNegative() << endl;
}

//Default Constructor
//create a template LinkedList
template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}

// Destructor - called automatically at end of
// program by compiler to free up memory on heap
template <typename T>
LinkedList<T>:: ~LinkedList() {
    Node * curr;
    while (head != nullptr) {
        curr = head;
        head = head->next;
        delete curr;
    }
}

//append elements to the LinkedList
//pass the data as parameter that want to append to the list
template <typename T>
void LinkedList<T>::append(T data) {
    Node * curr;
    Node * newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;
    //when the LinkedList is empty, add the new node to the head of the list
    if(head == nullptr) {
        head = newNode;
    }
    else {
        //add new node to the end of the list
        curr = head;
        while (curr->next != nullptr) {
            curr = curr->next; //traverse the LinkedList
        }
        curr->next = newNode;
    }
}

//get the last negative number in the list
//return the last negative number


template <typename T>
T LinkedList<T>::getLastNegative() {

    return getLastNegative(head, 0);
//    Node * curr = head;
//    T result = 0; //when there is no negative number, return 0
//    while (curr != nullptr) {
//        if (curr->data < 0)
//            result = curr->data; //update the newest negative value
//        curr = curr->next;//make sure not call the data at nullptr
//    }
//      return result; //return the number
//
}

template <typename T>
T LinkedList<T>::getLastNegative(Node * ptr, T temp) {
    if(ptr == nullptr){
        return temp;
    }
    if (ptr->data < 0) {
        T temp = ptr->data;
        return getLastNegative(ptr->next, temp);
    }
    return getLastNegative(ptr->next, temp);
}

template <typename T>
T LinkedList<T>::getSum() const {
    return getSum(head);
}
template <typename T>
T LinkedList<T>::getSum(Node* ptr) const {
    if(ptr != nullptr) {
        return getSum(ptr->next) + ptr->data;
    }
    return 0;
}

//display information in the LinkedList
template <typename T>
string LinkedList<T>:: to_string() const {
    stringstream ss;
    Node * curr = head;
    while (curr != nullptr) {
        ss << curr->data << " ";
        curr = curr ->next;
    }
    ss << "\n";
    return ss.str();
}
