// AUTHOR:   Shunuo Chen
// FILENAME: BookList.h
// DATE:     10/14/2022
// PURPOSE: Describe the purposed and behaviors of the BookList class, which
//          is used to store books information with an array
#ifndef P1_BOOKLIST_H
#define P1_BOOKLIST_H
#include <string>
using namespace std;

class BookList {
public:
    BookList(int);  // Constructor accepts initial capacity of list
    ~BookList();    // Destructor - Used to free up memory on heap
    BookList(const BookList&); //copy constructor, used to copy the BookList
                                //object
    BookList& operator=(const BookList&); //overloaded =operator
    void add(string, string, string); // add element to array, pass in author
    //author name, book title, and year published
    bool empty() const;     // determines if list is empty or not
    int size() const;       // number of elements in array
    string getBookInformation (int); //get stored book information. pass
                                //ISBN number
    string to_string() const; //used to display information in the clas


private: //only use to stor
    //create a book struct to store books' information
    struct Book {
        string author; //book author
        string title; //book title
        string year; //book year
        int isbnNumber; //book's ISBN number
    };

    Book* array;   // Pointer to the array
    int capacity;  // capacity of array
    int bookCount = 0; //Number of array
    int ISBN = 1; //Number of books
    void resize(); // resize array (when full
};

#endif //P1_BOOKLIST_H
