//
// Created by Chloooooe on 10/3/22.
//

#ifndef LAB2_BOOKLIST_H
#define LAB2_BOOKLIST_H
#include <string>
using namespace std;

class BookList {
public:
    BookList(int);  // Constructor accepts initial capacity of list
    ~BookList();    // Destructor - Used to free up memory on heap
    BookList(const BookList&); //copy constructor
    BookList& operator=(const BookList&); //overloaded =operator
    void add(string, string, string); // add element to array
    bool empty() const;     // determines if list is empty or not
    int size() const;       // number of elements in array
    string to_string() const;

private: //only use to store
    struct Book {
        string author;
        string title;
        string year;
        int isbnNumber;
    };

    Book* array;   // Pointer to the array
    int capacity;  // capacity of array
    int bookCount = 0; // Number of array
    int ISBN = 1; //Number of books
    void resize(); // resize array (when full)
};

#endif //LAB2_BOOKLIST_H
