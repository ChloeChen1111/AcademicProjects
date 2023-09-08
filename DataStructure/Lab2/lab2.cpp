#include <iostream>
#include <fstream>
#include <sstream>
#include "BookList.h"

using namespace std;

int main() {
    const int CAPACITY = 100;
    BookList bookList = BookList(CAPACITY);
    //create a string variable tpo hold the file name
    string fileName;
    //create an instance of the ifstream,
    ifstream inFile;

    //prompt user to enter file name
    cout << "Enter books file: ";
    //read user's input
    getline(cin, fileName);
    //open the file
    inFile.open(fileName);

    string line, author, title, year;

    //verify that it was opened
    if(inFile.is_open()) {
        while(getline(inFile,line)) {
            stringstream ss;
            ss << line;
            getline(ss, author, ',');
            getline(ss, title,',');
            getline(ss, year,',');

            bookList.add(author, title, year);
        }
    }
    else  {
        cout << "The file you entered cannot be opened";
    }

    cout << endl << "# of books: " << bookList.size() << endl <<endl;
    cout << bookList.to_string();

    //BookList* copyObj = new BookList(bookList);
    //cout << copyObj->to_string();

//    BookList testObj = bookList;
//    cout << testObj.to_string();
    return 0;
}
