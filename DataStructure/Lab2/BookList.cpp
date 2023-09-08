//
// Created by Chloooooe on 10/3/22.
//

#include "BookList.h"
#include<sstream>
//Default Constructor
//Accepts capacity and creates new list on heap
BookList::BookList(int cap) {
    array = new Book[cap];
    capacity = cap;
}
// Destructor - called automatically at end of
// program by compiler to free up memory on heap
BookList::~BookList() {
    delete [] array;
}

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


BookList& BookList::operator=(const BookList &obj) {
    // check if you're assigning an object to itself
    if(this!= &obj) {

        // deallocate memory
        delete array;
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

void BookList::add(string author, string title, string year) {
    // Check that we haven't reached capacity
    if(bookCount >= capacity) {
        resize();
    }
    Book temp;
    temp.author = author;
    temp.title = title;
    temp.year = year;
    temp.isbnNumber = ISBN; //Assign BookList field to the struct field

    // Use bookCount to access next free space in list
    array[bookCount] = temp;
    bookCount++;
    ISBN++;
}

bool BookList::empty() const {
    return bookCount == 0;
}

int BookList::size() const {
    return bookCount;
}

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
//display message
string BookList::to_string() const {
    stringstream ss;
    for (int i = 0; i < bookCount; i++) {
        ss << array[i].isbnNumber << ", " << array[i].author << ", ";
        ss << array[i].title << ", " << array[i].year <<endl ;
    }
    return ss.str();
}