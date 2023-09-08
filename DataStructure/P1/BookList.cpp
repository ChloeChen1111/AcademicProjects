// AUTHOR:   Shunuo Chen
// FILENAME: BookList.cpp
// DATE:     10/14/2022
// PURPOSE: Implementation for BookList described in BookList.h

#include "BookList.h"
#include<sstream>

using namespace std;
//Default Constructor
//Accepts capacity and creates new list on heap
BookList::BookList(int cap) {
    array = new Book[cap];
    this -> capacity = cap;
}

// Destructor - called automatically at end of
// program by compiler to free up memory on heap
BookList::~BookList() {
    delete [] array;
}

//copy object
//the constructor automatically generate a new object which
//has exactly the same thing with the original object
BookList::BookList(const BookList &obj) {
    //assign capacity from obj
    capacity = obj.capacity;

    //allocate memory based on new capacity
    array = new Book[capacity];
    //copy over elements from obj
    for (int i = 0; i < obj.size(); i++) {
        Book temp = obj.array[i];
        //add new Book elements to the new array in the new object
        add(temp.author, temp.title, temp.year);
    }
}

//operator=
BookList& BookList::operator=(const BookList &obj) {
    // check if you're assigning an object to itself
    if(this!= &obj) {
        // deallocate memory
        delete [] this -> array;
        this->capacity = obj.capacity;

        // allocate memory based on new capacity
        this->array = new Book[capacity];
        // copy over elements (from obj)
        for (int i = 0; i < obj.size(); i++) {
            Book temp = obj.array[i];
            //add new Book elements to the new array in the new object
            add(temp.author, temp.title, temp.year);
        }
    }
    // return object
    return *this;
}

//add books to the book list
void BookList::add(string author, string title, string year) {
    // Check that we haven't reached capacity
    if(bookCount >= capacity) {
        resize();
    }
    Book temp; //create an instance of the book struct
    temp.author = author;
    temp.title = title;
    temp.year = year;
    temp.isbnNumber = ISBN; //Assign BookList field to the struct field

    // Use bookCount to access next free space in list
    array[bookCount] = temp;
    bookCount++;
    ISBN++;
}
//Check if the booklist is empty
bool BookList::empty() const {
    return bookCount == 0;
}

//get size of the booklist
int BookList::size() const {
    return bookCount;
}

//resize the booklist when the capacity is full
void BookList::resize() {
    // update capacity to twice its current size
    capacity *= 2;

    // create new array based on updated capacity
    Book * tempArr = new Book[capacity];
    // copy old array values to new array
    for (int i = 0; i < bookCount; i++) {
        tempArr[i] = array[i];
    }
    // delete old array
    delete [] array;
    // reassign old array to new array
    array = tempArr;
}

//get books information stored in the booklist (at a specific index)
// with ISBN number
string BookList::getBookInformation(int isbnNumber) {
    int i = isbnNumber - 1; //index of the string array with book information
    //convert int isbn number to string with :: to_string function
    string isbn = ::to_string(array[i].isbnNumber);
    //assign author, title, and year to the string array
    string author = array[i].author;
    string title = array[i].title;
    string year = array[i].year;
    //return a string with books information
    return isbn + ", " + author + ", " + title +  ", " + year;
}

//display information in the BookList
string BookList::to_string() const {
    stringstream ss; //create an instance of stringstream class to store
    //booklist information in the instance, then return the stored string
    for (int i = 0; i < bookCount; i++) {
        ss << array[i].isbnNumber << ", " << array[i].author << ", ";
        ss << array[i].title << ", " << array[i].year << endl;
    }
    return ss.str();
}
