// AUTHOR:   Shunuo Chen
// FILENAME: HashTable.h
// DATE:     11/20/2022
// PURPOSE:  Describe the purposed and behaviors of the HashTable class, which
//           is used to store array element
#ifndef LAB6_HASHTABLE_H
#define LAB6_HASHTABLE_H

#endif //LAB6_HASHTABLE_H
using namespace std;

class HashTable {
public:
    HashTable(int capacity); //constructor
    ~HashTable(); //destructor
    int put(int key, int value); //put key and value pair into the hash table
    int get(int key); //use key to get specific value paired with the key
    bool contains(int key); //check if the hashtable contains a specific key
    int size(); //get the size of the hashtable
    bool empty(); //check if the hashtable is empty

private:
    //create a Bucket to store in the array
    struct Bucket {
        int key = -1;
        int value = -1;
    };
    //initialize the array
    Bucket* array;
    //capacity of the array
    int capacity;
    int hash(int key); //hash function to get the correct index
                       // to put key and value pairs
    int count = 0;//initialize the size of the array
};

//Default Constructor
//Accepts capacity of the array
HashTable::HashTable(int capacity) {
    this -> capacity = capacity;
    array = new Bucket[capacity];
}

//Destructor
HashTable:: ~HashTable() {
    delete [] array;
}

//The hash function get correct index of the key
int HashTable:: hash(int key) {
    return key%capacity;
}

//The put function add element to the array
//Accepts key and value stored in the array
int HashTable:: put(int key, int value) {
    //When the table is empty, add key and value to the table at correct index
    if(array[hash(key)].key == -1) {
        array[hash(key)].key = key;
        array[hash(key)].value = value;
        count++; //increment the size of the array when add
        return -1;
        //when the key exists, replace value at the key with new value
        //overwrite the value at a key
    } else if (array[hash(key)].key == key) {
        //hold the value at the key to return
        int result = array[hash(key)].value;
        array[hash(key)].value = value;
        return result;
        //when collision occurs
        //linear probing to get the empty position to insert key and value
    } else {
        int i = 1;
        while (array[hash(key + i)].key != -1) {
            if(array[hash(key + i)].key == key) {
                int result = array[hash(key + i)].value;
                array[hash(key + i)].value = value;
                return result;
            }
            i++; //increment i to find correct index
        }
        //add key and value at the index
        array[hash(key + i)].key = key;
        array[hash(key + i)].value = value;
        count++; //increment the size of the array
        return -1;
    }
}

//The get function get value at a specific key
//Accepts key stored in the array
int HashTable:: get(int key) {
    //when find the key, return value at the key
    if (array[hash(key)].key == key) {
        return array[hash(key)].value;
    } else {
        //when there was collision, find the correct key and return
        //value at the key
        int i = 1;
        while(array[hash(key + i)].key != -1) {
            if (array[hash(key + i)].key == key) {
                return array[hash(key + i)].value;
            }
            i++; //increment i to get the correct position
        }
    }
    return -1;
}

//check if the HashTable contains the specific key
bool HashTable:: contains(int key) {
    //when found the key, return true
    if(array[hash(key)].key == key ) {
        return true;
    }
    //using linear probing to find the key, when found, return true
    //if the key is not contained, return false.
    else {
        int i = 1;
        while(array[hash(key + i)].key != -1) {
            if(array[hash(key + i)].key  == key) {
                return true;
            }
            i++;
        }
        return false;
    }
}

//get the size of the hashtable
int HashTable:: size() {
    return count;
}

//check if the table is empty
bool HashTable:: empty() {
    return count == 0;
}

