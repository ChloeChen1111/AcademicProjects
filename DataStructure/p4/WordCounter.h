// AUTHOR:   Shunuo Chen
// FILENAME: WordCounter.h
// DATE:     12/01/2022
// PURPOSE:  Describe the purposed and behaviors of the WordCount class, which
//           is used to store word information with an array of linkedlist
#include <string>
#ifndef P4_FILES_WORDCOUNTER_H
#define P4_FILES_WORDCOUNTER_H

using namespace std;

class WordCounter {
public:
    WordCounter(int capacity); //constructor
    ~WordCounter(); //destructor
    WordCounter(const WordCounter &); // Copy constructor
    WordCounter& operator= (const WordCounter&);// Overloaded = operator
    // If the word does not exist, add a word to the table
    //If the word does exist, increments the count of the given word in the hash table.
    void addWord(string word);

    void removeWord(string word); //remove a word from the table
    int getWordCount(string word); //get the word count of a specific word
    int getCapacity() const; //get capacity of the array
    int getUniqueWordCount() const; //get the unique word count
    int getTotalWordCount() const; //get the total word count
    bool empty() const; //check if the array is empty

private:
    //create a Bucket struct to store word, frequency and the pointer
    struct Bucket {
        string word ; // value of the table
        int frequency = 0; //key of the table
        Bucket* next = nullptr; //pointer pointing to the next Bucket
    };

    int capacity; //capacity of the array
    Bucket ** array; //Pointer to the array of head pointers(of the linked list)
    int hashCode(string word); //hashCode function to get the hashCode of a word
    int totalWordCount = 0; //initialize the total word count to 0
    int uniqueWordCount = 0;//initialize the unique word count to 0
};
WordCounter::WordCounter(int capacity) {
    this -> capacity = capacity;
    array  = new Bucket *[capacity];
    for (int i = 0; i < capacity; i++) {
        array[i] = nullptr;
    }
}
//destructor
WordCounter:: ~WordCounter() {
    Bucket *curr;
    for (int i = 0; i < capacity; i++) {
        curr = array[i];
        while(curr != nullptr){
            Bucket * temp = curr;
            curr = curr->next;
            delete temp;
        }
        array[i] = nullptr;
    }
    delete[] array;
    array = nullptr;
}

//copy constructor
//Accepting WordCounter object
WordCounter::WordCounter(const WordCounter &obj) {
    capacity = obj.capacity;
    // allocate memory based on new capacity
    array = new Bucket* [capacity];
    //copy buckets in array[i]
    for(int i = 0; i < capacity; i++) {
        Bucket *sourcePtr = obj.array[i];
        //copy each element in the bucket
        if(sourcePtr != nullptr) {
            array[i] = new Bucket; //create a new Bucket in target object
            Bucket *targetPtr = array[i];//pointing to the new Bucket
            targetPtr->word = sourcePtr->word; //copy elements in array[i]
            targetPtr->frequency = sourcePtr->frequency;
            while(sourcePtr->next != nullptr) {
                targetPtr->next = new Bucket;
                targetPtr->next->word = sourcePtr->next->word;
                targetPtr->next->frequency = sourcePtr->next->frequency;
                sourcePtr = sourcePtr->next;
                targetPtr = targetPtr->next;
            }
        }
    }
    this->totalWordCount = obj.totalWordCount;
    this->uniqueWordCount = obj.uniqueWordCount;
}

//overloaded operator=
//Accepting WordCounter object
WordCounter& WordCounter:: operator= (const WordCounter &obj) {
    Bucket * curr;
    if(this != &obj) {
        //copy buckets in array[i]
        for (int i = 0; i < capacity; i++) {
            curr = array[i];
            while(curr != nullptr){
                Bucket * temp = curr;
                curr = curr->next;
                delete temp;
            }
            array[i] = nullptr;
        }
        delete[] array;
        array = nullptr;
    }
    capacity = obj.capacity;
    // allocate memory based on new capacity
    array = new Bucket* [capacity];
    for(int i = 0; i < capacity; i++) {
        Bucket *sourcePtr = obj.array[i];
        //copy each element in the bucket
        if(sourcePtr != nullptr) {
            array[i] = new Bucket; //create a new Bucket in target object
            Bucket *targetPtr = array[i];//pointing to the new Bucket
            targetPtr->word = sourcePtr->word; //copy elements in array[i]
            targetPtr->frequency =sourcePtr->frequency;
            while(sourcePtr->next != nullptr) {
                targetPtr->next = new Bucket;
                targetPtr->next->word = sourcePtr->next->word;
                targetPtr->next->frequency = sourcePtr->next->frequency;
                sourcePtr = sourcePtr->next;
                targetPtr = targetPtr->next;
            }
        }
    }
    this->totalWordCount = obj.totalWordCount;
    this->uniqueWordCount = obj.uniqueWordCount;
    return *this;
}

//get correct index of the key
//key is the word, value is the frequency of ech word
int WordCounter:: hashCode(string word) {
    hash<string> H;
    size_t hashCode = H(word);
    int index = hashCode % capacity;
    return index;
}

//addWord function to get word to the linked list at the array correct index
//Accepting string word needed to add
void WordCounter::addWord(string word) {
    //increment the totalWordCount
    totalWordCount++;

    //get the correct index
    int index = hashCode(word);

    //when the head of the linked list at array[index] is empty
    //add the Bucket to the array[index]
    if(array[index] == nullptr) {
        //create a new Bucket
        Bucket * headNode = new Bucket;
        //store the passed in word
        headNode->word = word;
        //add the frequency of the word
        headNode->frequency = 1;
        //store the bucket at the array[index]
        array[index] = headNode;
        //increment the uniqueWordCount
        uniqueWordCount++;
    } else {
        //when the head node at array[index] is not empty
        //start to traverse the linkedlist
        Bucket *tempBucketPtr = array[index];
        //get out of the while loop when we get the end of the linked list
        //or we found our target word
        while (tempBucketPtr->next != nullptr &&
               tempBucketPtr->word.compare(word) != 0) {
            //pointing to the next bucket
            tempBucketPtr = tempBucketPtr->next;
        }
        //check if we get the target word, once find, update the
        // word's frequency
        if(tempBucketPtr->word.compare(word) == 0) {
            // update old bucket
            tempBucketPtr->frequency++;
        } else {
            //if the get the end of the linked list but not find the target word
            // create new bucket to store the new word, then increment the
            //uniqueWordCount
            uniqueWordCount++;
            Bucket *next = new Bucket;
            next->word = word;
            next->frequency = 1;
            //connect the linkedlist with the new bucket
            tempBucketPtr->next = next;
        }
    }
}
//remove word in the array of linkedlist
//Accepting word as the parameter
void WordCounter::removeWord(string word){
    //find the correct index of the word
    int index = hashCode(word);
    //if there is nothing in the array[index], return
    if (array[index] == nullptr){
        return;
    }
    //when we found the target word in the array[index] pointer pointed bucket
    //(which is the head of the linkedlist)
    //create a pointer pointing to the array[index]
    Bucket *head = array[index];
    //when the head node has the target word
    if (array[index]->word.compare(word) == 0) {
        //store the next bucket to the array[index] to remove array[index]
        array[index] = head->next;
        //update the totalWordCount
        totalWordCount -= head->frequency;
        //decrement the uniqueWordCount
        uniqueWordCount--;
        //delete the head pointer pointed bucket(array[index])
        delete head;
        return;
    }
    //Start to traverse the linkedlist
    //create two pointer to point the head
    Bucket * curr = head;
    Bucket * prev = head;
    //traverse the linked list until get the end of the linkedlist or get the
    //target word
    while (curr != nullptr && curr->word.compare(word) != 0){
        prev = curr; //let prev points to curr
        curr = curr->next; //let curr pointing to the next bucket
    }
    //only delete the bucket when we found it
    //this means we found the word
    if(curr != nullptr) {
        prev->next = curr->next;
        //update the totalWordCount
        totalWordCount -= curr->frequency;
        //decrement the uniqueWordCount
        uniqueWordCount--;
        //delete the target bucket
        delete curr;
    }
}

//get frequency of specific word
//accepting target word
int WordCounter:: getWordCount(string word) {
    //find the correct index of the word
    int index = hashCode(word);
    //if here the array[index] points to nothing
    Bucket *head = array[index];
    if(head == nullptr) {
        return 0;
    }
    //when we find the target word, return its frequency
    if (head->word == word) {
        return array[index]->frequency;
    }
    //traverse the linkedlist until we get the target word or get end of the
    //linkedlist
    while (head->next != nullptr && head->next->word != word) {
        head = head->next;
    }
    //check if we get the end of the linkedlist first
    if (head->next == nullptr) {
        return 0;
    } else {
        //once we find the target word, return the frequency of the word
        return head->next->frequency;
    }
}

//check if the array is empty
bool WordCounter:: empty() const {
    return totalWordCount == 0;
}

//get the capacity of the array
int WordCounter:: getCapacity() const {
    return capacity;
}

//get the total word count
int WordCounter:: getTotalWordCount() const {
    return totalWordCount;
}

//get the unique word count
int WordCounter:: getUniqueWordCount() const {
    return uniqueWordCount;
}
#endif //P4_FILES_WORDCOUNTER_H
