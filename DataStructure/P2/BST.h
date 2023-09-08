//
// Created by Chloooooe on 10/24/22.
//

#ifndef P2_BST_H
#define P2_BST_H
#include <string>
#include <sstream>
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
    //Searches the BST to determine if a given value is present.
    //Returns true if so, else false. Pass the target value
    bool contains(T);
    //Removes the specified value from the BST. Pass the target value
    void remove(T);
    bool empty(); //Determines if BST is empty. Returns true if so, else false.
    int size(); //  Returns the count of nodes in the BST.
    //Returns the count of nodes in the BST that do not have any children.
    int getLeafCount();
    //Returns height of the BST. The height of the tree is the node
    // with the greatest depth.
    int getHeight();
    //Returns the level of a node in the BST. If the node with the
    // given value is not present in the BST, returns -1.
    int getLevel(T);
    //Returns a string of elements in the order specified by
    //the in-order traversal of the BST. Pass the target value
    string getInOrderTraversal();
    //Returns a string of elements in the order specified by
    //the pre-order traversal of the BST.
    string getPreOrderTraversal();
    //Returns a string of elements in the order specified by
    //the post-order traversal of the BST.
    string getPostOrderTraversal();
    //returns expected values in a known BST.
    string getAncestors(T);

private:
    //create a Node struct in the BST
    struct Node {
        T element; //elements stored in the tree node
        Node* left; //left pointer
        Node* right; //right pointer
    };
    Node* root; //create a root of the tree
    void copyHelper(const Node *, Node *&); //copy helper function
    void destroyTree(Node *&); //destory the tree
    void insert(Node *&, Node *&); //insert helper function
    bool contains(Node *&, T);//contains helper function
    void remove(Node *&, T); //remove helper function
    void makeDeletion(Node *&, T); //delete a specific node
    int size(Node *&); //size helper function
    int getLeafCount(Node *&); //get leaf helper function
    int getHeight(Node *&); //get height helper function
    int getLevel(Node *&, T, int); //get level helper function
    //traversal helper function
    void getInOrderTraversal(Node *&, stringstream &);
    //traversal helper function
    void getPreOrderTraversal(Node *&, stringstream &);
    //traversal helper function
    void getPostOrderTraversal(Node *&, stringstream &);
    //get ancestors helper function
    bool getAncestors(Node *&, T, stringstream &);
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
    //"this" is a pointer pointing to the object itself, in this case,
    //"this->root" points to the root
    copyHelper(obj.root, this->root);
}

//copy constructor helper
template <typename T>
void BST<T>:: copyHelper(const Node *oldOne, Node *&newOne ) {
    if(oldOne != nullptr) {
        //create a new Node
        //only pass by reference can make the root point to the new Node
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
        //destory the existing elements in the new BST
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

//check if the BST contains the specific node
//accept the target item
template <typename T>
bool BST<T>::contains(T item) {
    //call the contains helper functoin with the target element and root of the
    //tree passed as parameters
    return contains(root, item);
}

//check if the BST contains the specific node
//accept root and target item
template <typename T>
bool BST<T>::contains(Node *& ptr, T item) {
    //when the root pointing to null, return false
    if (ptr == nullptr) {
        return false;
    } else {
        //when find the target item, return true
        if (ptr->element == item) {
            return true;
        }
        //when the target item is smaller than the element in the node
        //find the element in the left subtree
        else if (ptr->element > item) {
           return contains(ptr->left, item);
        } else {
            //when the target item is greater than the element in the node
            //find the element in the right subtree
            return contains(ptr->right, item);
        }
    }
}

//remove the target node
//accept target item
template <typename T>
void BST<T>::remove(T item) {
    //call the helper function to get search for the target node
    //with the target element and root of the tree passed as parameters
    remove(root, item);
}

//search the target node and remove it
//accept root and target item
template <typename T>
void BST<T>::remove(Node *&ptr, T item) {
    //check if root contains items
    if (ptr != nullptr) {
        //( this part is searching
        //when the target item is smaller than the element in the node
        //search the element in the left subtree
        if (ptr->element > item)
            remove(ptr->left, item);
            //when the target item is greater than the element in the node
            //search the element in the right subtree
        else if (ptr->element < item)
            remove(ptr->right, item);
        else
            //once we find the target, we delete
            //pass the pointer pointing to the root
            makeDeletion(ptr, item);
    }
}

//delete the target node
//accept root and target item
template <typename T>
void BST<T>:: makeDeletion(Node *&ptr, T item) {
    Node * curr = nullptr; //create a pointer
    //verify there is a node there
    if (ptr != nullptr) {
        // satisfy the two cases: no children or right child
        if (ptr->left == nullptr) {
            curr = ptr; //hold the node to delete later
            ptr = ptr->right; //connect the right side children
            delete curr;
        } else if (ptr->right == nullptr) {
            curr = ptr;
            ptr = ptr->left;
            delete curr; //no child
            //2 children, neither left nor right is null
        } else {
            //pointing to the target node successor
            curr = ptr->right;
            //to get the smallest value of the right subtree
            //to replace the deleted node
            while (curr->left != nullptr) {
                curr = curr->left; //find the successor
            }
            //replacing the target data with the successor's data
            ptr->element = curr->element;
            //call remove to delete the successor
            remove(ptr->right, curr->element);
            //pass the ptr-> right
        }
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

//get the number of leaves in the BST
template <typename T>
int BST<T>::getLeafCount() {
    //call the helper function
    return getLeafCount(root);
}

//helper function to get the leaf node
//accept the root
template <typename T>
int BST<T>::getLeafCount(Node *&ptr) {
    if(ptr == nullptr)
        return 0;
    //when the left and right pointers pointing to nullptr, get the leaf node
    if(ptr->left == nullptr && ptr->right == nullptr) {
        return 1;
    }
    else {
        //finding the target node in both left and rigtht subtree
        return getLeafCount(ptr->left) + getLeafCount(ptr->right);
    }
}

//get the height of the tree
template<typename T>
int BST<T>:: getHeight() {
    //call the helper function
    return getHeight(root);
}

//helper function get the height of the tree
//accept the root
template <typename T>
int BST<T>:: getHeight(Node *&ptr) {
    //when the root of the tree pointing to null, return -1
    if(ptr == nullptr) {
        return -1;
    }
    //get height of the left subtree
    int leftHeight = getHeight(ptr->left);
    //get height of the right subtree
    int rightHeight = getHeight(ptr->right);
    //return the greater height plus the distance to the root
    if(leftHeight >= rightHeight) {
        return 1 + leftHeight;
    }
    else {
        return 1 + rightHeight;
    }
}

//get level of the BST
template <typename T>
int BST<T>::getLevel(T target) {
    return getLevel(root, target, 0);
}

//helper function get the level of the tree
//accept the root
template <typename T>
int BST<T>:: getLevel(Node *&ptr, T target, int level) {
    //when the root of the tree pointing to null, return -1
    if (ptr == nullptr) {
        return -1;
    }
    //when the target item is smaller than the element in the node
    //get level in the left subtree
    if (ptr->element > target) {
        return getLevel(ptr->left, target, level + 1);

    } else if (ptr->element < target) {
        //when the target item is greater than the element in the node
        //get level in the right subtree
        return getLevel(ptr->right, target, level + 1);
    } else {
        //once find the target item, return the level
        return level;
    }
}

//get the BST in a in-order traversal
template <typename T>
string BST<T>::getInOrderTraversal() {
    stringstream ss;
    getInOrderTraversal(root, ss);
    return ss.str();
}

//get the BST in a in-order traversal
//accept root and instance of stringstrem
template <typename T>
void BST<T>::getInOrderTraversal(Node *&ptr, stringstream &ss) {
    if(ptr != nullptr) {
        getInOrderTraversal(ptr->left, ss);
        ss << ptr->element << " ";
        getInOrderTraversal(ptr->right, ss);
    }
}

//get the BST in a pre-order traversal
template <typename T>
string BST<T>::getPreOrderTraversal() {
    stringstream ss;
    getPreOrderTraversal(root, ss);
    return ss.str();
}

//get the BST in a pre-order traversal
//accept root and instance of stringstrem
template <typename T>
void BST<T>::getPreOrderTraversal(Node *&ptr, stringstream &ss) {
    if(ptr != nullptr) {
        ss << ptr->element << " ";
        getPreOrderTraversal(ptr->left, ss);
        getPreOrderTraversal(ptr->right, ss);
    }
}

//get the BST in a post-order traversal
template <typename T>
string BST<T>::getPostOrderTraversal() {
    stringstream ss;
    getPostOrderTraversal(root, ss);
    return ss.str();
}

//get the BST in a post-order traversal
//accept root and instance of stringstrem
template <typename T>
void BST<T>:: getPostOrderTraversal(Node *&ptr, stringstream &ss){
    if(ptr != nullptr) {
        getPostOrderTraversal(ptr->left, ss);
        getPostOrderTraversal(ptr->right, ss);
        ss << ptr->element << " ";
    }
}
//get ancestor of a target value
//accept the target value
template <typename T>
string BST<T>::getAncestors(T target) {
    stringstream ss;
    getAncestors(root, target, ss);
    return ss.str();
}

//get ancestor of a target value
//accept the root, target value, instance of stringstream
template <typename T>
bool BST<T>::getAncestors(Node *& ptr, T target, stringstream &ss) {
    //when the BST root is pointing to null, return false
    if(ptr == nullptr) {
        return false;
    }
    //when find the target value, return true
    if(ptr->element == target) {
        return true;
    }
    //searching in the left subtree when the target is smaller
    // than the prt value
    if (ptr->element > target) {
        if (getAncestors(ptr->left, target, ss)) {
            //diaply the ancestor
            ss << ptr->element << " ";
            return true;
        }
        return false;

    } else {
        //searching in the right subtree when the target is greater
        // than the prt value
        if(getAncestors(ptr->right, target, ss)) {
            //diaply the ancestor
            ss << ptr->element << " ";
            return true;
        }
        return false;
    }
}
#endif //P2_BST_H
