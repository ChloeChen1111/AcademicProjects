// AUTHOR:   Shunuo Chen
// FILENAME: L3.cpp
// DATE:     10/16/2022
// PURPOSE:  This program informs the user if the input was a palindrome.
// INPUT:    The context from the input file from
// PROCESS:  Read the input information, and remove space from the input
//           string, then check if the string is a palindrome
// OUTPUT:   Prints the input string is a palindrome or not

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

string removeSpace(string);
// remove space from the input string
// IN: the input string as parameter
// MODIFY: none
// OUT: string without any space

bool isPalindrome(string);
// check if the input string is palindrome
// IN: the input string without any space
// MODIFY: none
// OUT: if the user's input is palindrome(bool)

int main() {
    cout << "Welcome to the palindrome testing program!" <<endl <<endl;
    string filename; //create a variable to hold the filename
    //prompt user to enter the file
    cout << "Enter the filename: ";
    cin >> filename;
    cout << endl;
    //create an instance of the ifstream
    ifstream inFile;
    //open the file
    inFile.open(filename);
    string input;
    //verify that it was opened
    if(inFile.is_open()) {
        //store string from the input file to the input
        while(getline(inFile, input)) {
            //call the removeSpace function get the string without any space
            string result = removeSpace(input);
            //check if the string is palindrome
            if(isPalindrome(result)) {
                cout << result << " is a palindrome!" << endl;
            }
            else
                cout << result << "is NOT a palindrome." << endl;
        }
    }
    cout << endl << "Thanks for using the palindrome tester!";
    return 0;
}

string removeSpace(string input) {
    stringstream ss(input);
    string result = "";
    string temp;
    //getline consider '' as delimiter and ignore the delimiter
    while(getline(ss, temp, ' ')) {
        result += temp;
    }
    return result;
}


bool isPalindrome(string result) {
    int left = 0; //initlize the left index to 0
    int right = result.size() - 1; //initialize the right index to the most
    //right index (size() - 1)
    if(result.size() <= 1) //return true when the string only have one char
        //the left and right index is keep updating
        return true;
    //make the char of the string to lower case
    char firstChar = tolower(result.at(left));
    char lastChar = tolower(result.at(right));
    left ++; //update the left index of the string
    right --; //update the right index of the string
    //use substr to update the string with updated indexes
    string middle = result.substr(left, right);
    //recursive to compare char in the string to determine if
    //it is palindrome
    return firstChar == lastChar && isPalindrome(middle);
}
