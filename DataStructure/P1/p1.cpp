// AUTHOR:   Shunuo Chen
// FILENAME: p1.cpp
// DATE:     10/14/2022
// PURPOSE:  This program prompts the user to input books.txt and ratings.txt;
//           We read the files and store information in the 2 files into
//           BookList, MemberList, and RatingList. Then we calculate members'
//           similarity of book ratings. Thus, we will recommend books to users
//           according to their taste
// INPUT:    User input of book.txt, and ratings.txt. The member, book, they
//           want to add into the booklist, memberlist, as well as ratng for a
//           book
// PROCESS:  Read the two file and store information in the two files. Then
//           calculates the similarity of members' book ratings. Allow users to
//           log in to view their ratings. Display book ratings of each member.
//           Recommend books to users based on their book ratings and the
//           similarity with other members
// OUTPUT:   Prints the function menus and display information according to
//           users' choose.

#include <iostream>
#include <fstream>
#include <sstream>
#include "BookList.h"
#include "MemberList.h"
#include "RatingList.h"
using namespace std;

const int BOOK_CAPACITY = 100; //constant book capacity
const int MEMBER_CAPACITY = 100; //constant member capacity
void welcome();
// display the welcome message
// IN: none
// MODIFY: none
// OUT: the welcome message

void readBooks(BookList*, RatingList*);
// read the book file
// IN: file with book information (BookList*, RatingList*)
// MODIFY: none
// OUT: none
void readRatings(RatingList*, MemberList*);
// read the rating file
// IN: file with rating information (RatingList*, MemberList*)
// MODIFY: none
// OUT: none

void getBookAndMemberNumber(RatingList*, MemberList*);
// get the number of books and members
// IN: (RatingList*, MemberList*)
// MODIFY: none
// OUT: number of books and number of members

void useMenu1(MemberList*, RatingList*, BookList*);
// allow user to use functions in the first menu
// IN: user's option (MemberList*, RatingList*, BookList*)
// MODIFY: none
// OUT: direct user to other functions according to their option

void loginToMenu2(MemberList*, RatingList*, BookList*);
// allow user to use functions in the second menu
// IN: user's option of the menu(MemberList*, RatingList*, BookList*)
// MODIFY: none
// OUT: member's ratings, and book recommendation

void displayMenu1();
// display the first menu
// IN: none
// MODIFY: none
// OUT: options on the first menu

void displayMenu2();
// display the second menu
// IN: none
// MODIFY: none
// OUT: options on the second menu

void addMember(MemberList*, RatingList*);
// add new member to the memberList
// IN: the member's info(account id and name)
// MODIFY: none
// OUT: none

void addBook(BookList*, RatingList*);
// add new book to the bookList
// IN: the member's info(account id and name)
// MODIFY: none
// OUT: none

bool validateOption(int, int);
// check if user's input is valid
// IN: user's option (int), and number of options(int)
// MODIFY: none
// OUT: if the user's input is valid(bool)

int main() {
    //Create instances of the BookList, RatingList, and MemberList classes
    BookList *bookList = new BookList(BOOK_CAPACITY);
    RatingList *ratingList = new RatingList(MEMBER_CAPACITY, BOOK_CAPACITY);
    MemberList *memberList = new MemberList(MEMBER_CAPACITY);

    welcome(); //display welcome message
    readBooks(bookList, ratingList);// read the book file
    readRatings(ratingList, memberList);// read the rating file
    getBookAndMemberNumber(ratingList,memberList);
    // get the number of books and members
    useMenu1(memberList, ratingList, bookList); //allow user to use menu1
    return 0;
}
void welcome() {
    cout << "Welcome to the Book Recommendation Program.\n" <<
         "The program will recommend you books based on your ratings\n" <<
         "Hope you like our recommendations!" << endl << endl;
}
void readBooks(BookList *bookList, RatingList *ratingList) {

    //create an instance of the ifstream,
    ifstream inFile;
    //create a variable to hold the filename
    string bookFile;
    cout << "Enter books file: ";

    bookFile = "../books.txt"; //don't forget to take input
    inFile.open(bookFile);

    string line, author, title, year;

    //verify that it was opened
    if(inFile.is_open()) {
        while(getline(inFile,line)) {
            stringstream ss;
            ss << line;
            getline(ss, author, ',');
            getline(ss, title,',');
             getline(ss, year,',');

            bookList->add(author, title, year);
            ratingList->addBook();
        }
    }
    else  {
        cout << "The file you entered cannot be opened";
    }
    inFile.close();

}

void readRatings(RatingList *ratingList, MemberList *memberList) {
    string memberName, ratingFile, ratingNum;
    int ratings;
    ifstream inFile;

    //get the filename from users
    cout << "Enter rating file: ";
    //read user's input
    //getline(cin, ratingFile);
    ratingFile = "../ratings.txt";
    cout << endl;
    //open the file
    inFile.open(ratingFile);

    int i = 0; //initialize i for member counts
    int j = 0; //initialize j for rating counts

    //verify that it was opened
    if (inFile.is_open()) {
        //reset the index of the string array
        i = 0;
        //control the while loop to read names from the file
        while (getline(inFile, memberName)) {
            memberList->addMember(memberName);//Store input string to the array
            ratingList->addMember();
            //get numbers from the input file and then split
            getline(inFile, ratingNum);
            //declare an instance of stringstream
            stringstream ss;
            //put string into ss
            ss << ratingNum;

            //reset the index of the inner array
            j = 0;
            //put ss into integer one by one
            while(ss >> ratings) {
                ratingList->updateRating(i+1, j+1, ratings);
                //Store input numbers to the 2D array
                //ratings[i][j] = number;
                j++; //increment the index of the 2D array (column)
            }
            i++; //increment the index of the 2D array (row)
        }
    }
    else {
        //display the error message when the file cannot be opened
        cout << "ERROR: cannot open the rating file.\n";
    }
    inFile.close(); //close the inFile object
}

void getBookAndMemberNumber(RatingList* ratingList, MemberList* memberList) {
    cout << "# of books: " << ratingList->getBookSize() << endl;
    cout << "# of members: " << memberList->size() << endl << endl ;
}
void useMenu1(MemberList* memberList,
              RatingList* ratingList,
              BookList* bookList) {
    int option = 0; //get into the while loop
    while(option != 4) {
        //display the menu
        displayMenu1();
        do {
            //prompt user to enter the options on the menu
            cout << "Enter a menu option: ";
            cin >> option;
            cin.ignore();
        }
        //check if their input is valid,
        while(!validateOption(option, 4));
        //direct user to the function they choose
        switch(option) {
            case 1:
                addMember(memberList, ratingList);
                break;
            case 2:
                addBook(bookList, ratingList);
                break;
            case 3:
                //allow user to login and see options on menu2
                loginToMenu2(memberList, ratingList, bookList);
                break;
            case 4:
                cout << "\nThank you for using the Book"
                     << " Recommendation Program!";
                break;
            default:
                break;
        }
    }
}

void loginToMenu2(MemberList* memberList,
                  RatingList* ratingList,
                  BookList* bookList) {
    int memberAccount;
    cout << "\nEnter member account: ";
    cin >> memberAccount;

    string memberName = memberList->getMemberName(memberAccount);
    cout << memberName << ", you are logged in!\n\n";
    //control the while loop to start
    int option = 0;
    while(option != 6) {
        //display the second menu
        displayMenu2();
        do {
            cout << "Enter a menu option: ";
            cin >> option;
            cout <<endl;
            cin.ignore();
        }
        while(!validateOption(option, 6));

        int oldRating;
        char answer;
        //direct user to get into the correct function according to their option
        switch(option) {
            case 1:
                addMember(memberList, ratingList);
                break;
            case 2:
                addBook(bookList, ratingList);
                break;
            case 3:
                cout << "Enter the ISBN for the book you'd like to rate: ";
                int isbn;
                cin >> isbn;
                oldRating = ratingList->getRating(memberAccount,isbn);
                if ( oldRating != 0) {
                    cout << "Your current rating for "
                            <<bookList->getBookInformation(isbn)
                            << " => rating: " << oldRating << endl;
                    cout << "Would you like to re-rate this book (y/n)? ";
                    cin >> answer;
                    if (answer != 'y') {
                        break;
                    }
                }
                cout << "Enter your rating: ";
                int rating;
                cin >> rating;
                ratingList->updateRating(memberAccount, isbn, rating);
                cout << "Your new rating for "
                        << bookList->getBookInformation(isbn)
                        << " => rating: " << rating << endl << endl;
                break;
            case 4:
                cout << ratingList->viewMemberRatings(memberAccount,
                                                      memberName,
                                                      bookList) << endl << endl;
                break;
            case 5:
                cout << ratingList->getRecommendations(memberAccount,
                                                       bookList,
                                                       memberList) << endl;
                break;

            case 6:
                break;

            default:
                break;
        }
    }
}

void displayMenu1() {
    cout << "************** MENU **************\n";
    cout << "* 1. Add a new member            *\n";
    cout << "* 2. Add a new book              *\n";
    cout << "* 3. Login                       *\n";
    cout << "* 4. Quit                        *\n";
    cout << "**********************************\n\n";

}
void displayMenu2() {
    cout << "************** MENU **************\n";
    cout << "* 1. Add a new member            *\n";
    cout << "* 2. Add a new book              *\n";
    cout << "* 3. Rate book                   *\n";
    cout << "* 4. View ratings                *\n";
    cout << "* 5. See recommendations         *\n";
    cout << "* 6. Logout                      *\n";
    cout << "**********************************\n\n";

}
void addMember(MemberList* memberList,
               RatingList* ratingList) {
    string memberName;
    cout << "Enter the name of the new member: ";
    getline(cin, memberName);

    memberList->addMember(memberName);
    ratingList->addMember();
    cout << memberName << " (account #: "
                    << memberList->size() << ") was added.\n\n";
}

void addBook(BookList* bookList, RatingList* ratingList) {
    string author, title, year;
    cout <<"Enter the author of the new book: ";
    getline(cin, author);
    //cin.ignore();

    cout <<"Enter the title of the new book: ";
    getline(cin, title);
    //cin.ignore();

    cout <<"Enter the year (or range of years) of the new book: ";
    getline(cin, year);

    bookList->add(author, title, year);
    ratingList->addBook();

    cout << bookList->size() << ", " << author << ", "
         << title << ", " << year << " was added.\n\n";
}
bool validateOption(int option, int optionNumber) {
    //make sure user enter the valid number
    if(option >= 1 && option <= optionNumber) {
        return true;
    }
    else {
        cout << "Sorry, you entered invalid option," <<
             "please enter 1-" << optionNumber << ".\n";
        return false;
    }
}
