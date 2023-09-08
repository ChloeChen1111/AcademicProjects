// AUTHOR:   Shunuo Chen
// FILENAME: LinkedList.h
// DATE:     10/20/2022
// PURPOSE:  Describe the purposed and behaviors of the LinkedList class, which
//           is used to store array element
#include <string>

#ifndef L4_LINKEDLIST_H
#define L4_LINKEDLIST_H

using namespace std;

//create a template LinkedList
template <typename T>
class LinkedList {
public:
    LinkedList(); //constructor
    ~LinkedList(); //destructor

    void append(T); //pass the data needed to append
    T getLastNegative(); //get the last negative element
    string to_string() const; //display information in the list
    T getSum() const;


private:
    //create a private struct template Node
    struct Node {
        T data; //element in the node
        Node * next; //node pointer
    };
    Node * head; //head of the Linkedlist
    T getSum(Node *ptr) const;
    T getLastNegative(Node * ptr, T temp);
};

#endif //L4_LINKED LIST_H