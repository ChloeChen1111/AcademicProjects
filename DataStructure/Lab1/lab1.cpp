// AUTHOR:  Shunuo Chen
// PROGRAM: Lab1.cpp
// DATE:    10/03/2022
// PURPOSE: The program let users enter a file
//          then read from the input file and store the information
//          to 2 arrays. Then display the 2 arrays
// INPUT:   files that includes authors' name and books' rating
// PROCESS: It opens the file and read from the file, then store the input
//          names to a string array, as well as store the ratings to a 2D
//          integer array, then display the 2 arrays.
// OUTPUT:  The authors' name with their book's rating

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
int main() {
    //create 2 variables to hold names and rating from the input file
    string name, rating;
     //create a int variable to hold translated numbers from the file
    int number;
    //create an instance of the ifstream,
    ifstream inFile;
    //create a variable to hold the filename
    string fileName;
    //Initialize size of the two arrays
    const int ROW = 100;
    const int COL = 100;
    //Create a dynamic array to stored strings from input file
    string *members = new string[ROW];

    //Create a 2D dynamic array
    //The rows of the "ratings" array is associated with the members
    //and the columns associated with the book ratings
    int **ratings = new int*[ROW];

    // populate the 2D array with elements
    for(int i = 0; i < ROW; i++) {
        ratings[i] = new int[COL];
    }
    //get the filename from users
    cout << "Enter rating file: ";
    //read user's input
    getline(cin,fileName);
    cout << endl;
    //open the file
    inFile.open(fileName);

    int i = 0; //initialize i for member counts
    int j = 0; //initialize j for rating counts

    //verify that it was opened
    if (inFile.is_open()) {
        //reset the index of the string array
        i = 0;
        //control the while loop to read names from the file
        while (getline(inFile, name)) {
            members[i] = name; //Store input string to the array

            //get numbers from the input file and then split
            getline(inFile, rating);
            //declare an instance of stringstream
            stringstream ss;
            //put string into ss
            ss << rating;

            //reset the index of the inner array
            j = 0;
            //put ss into integer one by one
            while(ss >> number) {
                //Store input numbers to the 2D array
                ratings[i][j] = number;
                j++; //increment the index of the 2D array (column)
            }
            i++; //increate the index of the 2D array (row)
        }
    }
    else {
        //display the error message when the file cannot be opened
        cout << "ERROR: cannot open file.\n";
    }
    inFile.close(); //close the inFile object
    int memberCount = i; //assign i to memberCount
    int ratingCount = j; //assign j to ratingCount

    //Display the message of rating count and memebr count
    cout << "# of books: " << ratingCount << endl;
    cout << "# of members: " << memberCount << endl << endl ;

    //display the two array
    for(int i = 0; i < memberCount; i++) {
        cout << members[i] <<endl;
        for(int j = 0; j < ratingCount; j++) {
            cout << ratings[i][j] << " ";
        }
        cout << endl;
    }
    //delete the array memebrs
    delete[] members;
   // delete the 2D array ratings;
    for (int i = 0; i < ROW; i++)
        delete [] ratings[i];
    delete [] ratings;
    ratings = nullptr;

    return 0;
}
