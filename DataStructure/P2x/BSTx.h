//
// Created by Chloooooe on 10/24/22.
//

#ifndef P2_BST_H
#define P2_BST_H
#include <string>
#include <sstream>
#include <queue>
using namespace std;

template <typename T>
class BST {
public:
    BST(); //constructor
    ~BST(); //destructor
    BST(const BST &); // Copy constructor
    BST& operator= (const BST &); // Overloaded = operator

    //Inserts the element passed in as a parameter into the BST.
    // Assume no duplicate values.Pass the target value
    void insert(T);
    bool empty(); //Determines if BST is empty. Returns true if so, else false.
    int size(); //  Returns the count of nodes in the BST.
    //get the largest number of nodes in the same level of the BST
    int getWidth();
    string getLevelOrder(); //display the tree in an level order

private:
    //create a Node struct in the BST
    struct Node {
        T element; //elements stored in the tree node
        Node* left; //left pointer
        Node* right; //right pointer
    };
    Node* root; //create a root of the tree
    void copyHelper(const Node *, Node *&); //copy helper function
    void destroyTree(Node *&); //destroy the tree
    int size(Node *&); //size helper function
    //get width helper function
    void getWidth(Node *&ptr, int *array, int level);

    void insert(Node *&ptr, Node *&newNode);
};

//Default Constructor
//create a template BST
template <typename T>
BST<T>::BST() {
    root = nullptr;
}

template <typename T>
//Destructor
//program by compiler to free up memory on heap
BST<T>:: ~BST() {
    //call the helper method to deaollcate memory
    destroyTree(root);
}
//destroyTree to destory the tree
//accept root
template <typename T>
void BST<T>::destroyTree(Node *&ptr) {
    //post order
    if (ptr != nullptr) {
        destroyTree(ptr->left);
        destroyTree(ptr->right);
        delete ptr;
    }
    ptr = nullptr;
}

//copy constructor
template <typename T>
BST<T>:: BST(const BST<T> &obj) {
    //pass the old object root and new object root as parameters
    copyHelper(obj->root, this->root);
}
//copy constructor helper
template <typename T>
void BST<T>:: copyHelper(const Node *oldOne, Node *&newOne ) {
    if(oldOne != nullptr) {
        //create a new Node
        newOne = new Node;
        //copy the element
        newOne->element = oldOne->element;
        //copy the pointer
        newOne->left = newOne->right = nullptr;
        //copy left subtree
        copyHelper(oldOne->left, newOne->left);
        //copy right subtree
        copyHelper(oldOne->right, newOne->right);
    }
    //newOne = nullptr is default, we dont need to write it again
}

//operator =
//CAN RETURN THE OBJ OF THE CLASS
template <typename T>
BST<T>& BST<T>::operator= (const BST<T> &oldObj) {
    if(this != oldObj) {
        //destroy the existing elements in the new BST
        destroyTree(this->root);
        //call the copy helper with old object root and new obejct root
        //to copy the old object
        copyHelper(oldObj->root, this->root);
    }
    //return the new object
    return *this;
}

//Inserts the element passed in as a parameter into the BST.
//accept target item
template <typename T>
void BST<T>:: insert(T item) {
    //create a new node to hold the element needed to insert
    Node* newNode = new Node;
    newNode->element = item;
    newNode->left = newNode->right = nullptr;
    //call the helper function pass the root and newNode with the element
    insert(root, newNode);
}

//insert helper function
//accept root and target item
template <typename T>
void BST<T>::insert(Node *&ptr, Node *& newNode) {
    //when the tree is null, add new node as a root
    if(ptr == nullptr) {
        ptr = newNode;
    }
        //add new element into the left subtree when the target element is smaller
        //than the element in the node
    else if(ptr->element > newNode->element) {
        insert(ptr->left, newNode);
    }
        //add new element into the right subtree when the target element is greater
        //than the element in the node
    else{
        insert(ptr->right, newNode);
    }
}

//check if the BST is empty
template <typename T>
bool BST<T>:: empty() {
    //when the root is pointing to null, return true
    //otherwise, return false
    return(root == nullptr);
}
//get size of the BST
template <typename T>
int BST<T>:: size() {
    //call the size helper function and pass root as parameter
    return size(root);
}
//get size helper function
//accept the root
template <typename T>
int BST<T>:: size(Node*& ptr) {
    if (ptr == nullptr) {
        return 0;
    } else {
        //add the root of the tree with sum of left subtree and right subtree
        return 1 + size(ptr->left) + size(ptr->right);
    }
}

//get With of the tree, the largest number of nodes in the same level.
template<typename T>
int BST<T>::getWidth() {
    //create a array to hold the number of nodes in different level
    int array[size()];
    //initialize the array
    for (int i = 0; i < size(); i++) {
        array[i] = 0;
    }
    //call the helper function
    getWidth(root, array, 0);
    int maxWidth = 0; //initialize the width to 0
    //get the maxWidth in the array
    for (int i = 0; i < size(); i++) {
        if(array[i] > maxWidth) {
            maxWidth = array[i];
        }
    }
    return maxWidth; //return the number of nodes
}
//helper function
//get With of the tree, the largest number of nodes in the same level.
//accepting Node, array, and level of the tree as parameter
template<typename T>
void BST<T>:: getWidth(Node *&ptr, int* array, int level) {
    //when the root is pointing to nullptr, return the function
    if (ptr == nullptr) {
        return;
    }
    array[level]++; //increment the array at a specific level when there is
    //a node at the level
    //get number of nodes in the left subtree in the next level
    getWidth(ptr->left, array, level + 1);
    //get number of nodes in the right subtree in the next level
    getWidth(ptr->right, array, level + 1);
}

template<typename T>
string BST<T>::getLevelOrder() {
    stringstream ss; //create an instance of stringstream
    queue<Node*> q; //create an instance of queue stores Node
    q.push(root); //add the root of the BST to the queue

    Node * ptr; //create a node pointer
    //stop the while loop when the queue is empty
    while (!q.empty()) {
        ptr = q.front(); //get the first node in the queue
        q.pop(); //take the first node in the queue
        //when the node is not pointing to null, store it to ss
        if(ptr != nullptr) {
            ss << ptr->element << " ";
            //push the left and right node to the queue
            q.push(ptr->left);
            q.push(ptr->right);
        }
    }
    return ss.str();
}


#endif //P2_BST_H

