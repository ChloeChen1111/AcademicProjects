// AUTHOR:   Shunuo Chen
// FILENAME: RatingList.cpp
// DATE:     10/14/2022
// PURPOSE: Implementation for RatingList described in RatingList.h
#include "RatingList.h"
#include "BookList.h"
#include "MemberList.h"
#include <string>
#include <sstream>

using namespace std;
//Default Constructor
//Accepts capacity and creates new ratingArray list on heap
RatingList::RatingList(int rowCap, int colCap) {
    ratingArray = new int*[rowCap];
    for(int i = 0; i < rowCap; i++) {
        ratingArray[i] = new int[colCap];
    }
    this->memberCap = rowCap;
    this->bookCap = colCap;
}

// Destructor - called automatically at end of
// program by compiler to free up memory on heap
RatingList::~RatingList() {
    for(int i = 0; i < memberCap; i++) {
        delete[] ratingArray[i];
    }
    delete [] ratingArray;
    ratingArray = nullptr;
}

//copy object
//the constructor automatically generate a new object which
//has exactly the same thing with the original object
RatingList::RatingList(const RatingList &obj) {
    //assign capacity from obj
    memberCap = obj.memberCap;
    bookCap =obj.bookCap;
    //allocate memory based on new capacity
    ratingArray = new int*[memberCap];
    for(int i = 0; i < memberCap; i++) {
        ratingArray[i] = new int[bookCap];
    }
    //copy over elements from obj
    for (int i = 0; i < obj.getMemberSize(); i++) {
        for(int j =0; j < obj.getBookSize(); j++) {
            ratingArray[i][j] = obj.ratingArray[i][j];
        }
    }
}
//operator=
RatingList& RatingList::operator=(const RatingList &obj) {
    // check if you're assigning an object to itself
    if (this != &obj) {
        // deallocate memory
        for(int i = 0; i < memberCap; i++) {
            delete[] ratingArray[i];
        }
        delete [] ratingArray;
        ratingArray = nullptr;

        // allocate memory based on memberCap and bookCap
        memberCap = obj.memberCap;
        bookCap =obj.bookCap;
        ratingArray = new int*[memberCap];
        for(int i = 0; i < memberCap; i++) {
            ratingArray[i] = new int[bookCap];
        }
        // copy over elements (from obj)
        for (int i = 0; i < obj.getMemberSize(); i++) {
            for(int j =0; j < obj.getBookSize(); j++) {
                ratingArray[i][j] = obj.ratingArray[i][j];
            }
        }
    }
    // return object
    return *this;
}

//update ratings in the ratingArray with memberAccount, ISBN as index
//memberAccount, ISBN, and rating are parameter
void RatingList::updateRating(int memberAccount, int ISBN, int rating) {
    ratingArray[memberAccount-1][ISBN-1] = rating;
}

//get the ratings with specific member of specific book
//return the rating at specific memberAccount and ISBN index
int RatingList:: getRating(int memberAccount, int ISBN) {
    return ratingArray[memberAccount-1][ISBN-1];
}
//view a member's all ratings
//member account, member name, and bookList are the parameters
string RatingList::viewMemberRatings(int accountId,
                                     string name,
                                     BookList* bookList) {
    //display the member's name
    string results = name + "'s ratings...\n";

    for (int i = 0; i < bookCount; i++) {
        //convert the returned rating (int) to string
        string rating = std::to_string(ratingArray[accountId-1][i]);
        //pass the ISBN number (i + 1) as parameter to get book information
        //store the member's name, book information, and rating to the results
        //string
        results += bookList->getBookInformation(i+1) + " ==> rating: " + rating
                + "\n";
    }
    //return the string to display member ratings
    return results;
}
//get the size of the ratingArray's row (number of members)
int RatingList::getMemberSize() const {
    return memberCount;
}

//get the size of the ratingArray's column (number of books)
int RatingList::getBookSize() const {
    return bookCount;
}


//add new member to the ratingArray
void RatingList::addMember() {
    memberCount++;
    //when the original capacity is full, resize the array
    if (memberCount > memberCap) {
        resizeMember();
    }
}

//add new book to the ratingArray
void RatingList::addBook() {
    bookCount++;
    //when the original capacity is full, resize the array
    if (bookCount > bookCap) {
        resizeBook();
    }
}

//Calculate the similarity of 2 members in the ratingArray, and get the index of
//the member who has the most similarity with the original member
//member Account is the parameter
int RatingList::getMostSimilarMember(int memberAccount) {
    //initlize the member index, maxSimilarity
    int memberIndex = memberAccount - 1;
    int maxSimilarity = -2147483648, tempSimilarity;
    int maxMember;

    for(int i = 0; i < memberCount; i++) {
        tempSimilarity = 0; //reinitialize tempSimilarity
        //avoid member to calculate the similarity with themselves
        if(i == memberIndex) {
            continue; //jump into the next outer for loop when the
            // member is calculating similarity with herself/himself
        }
        //calculate the similarity with all other members'
        // ratings in the list
        for(int j = 0; j < bookCount; j++) {
            //hold the similarity
            tempSimilarity += ratingArray[memberIndex][j] * ratingArray[i][j];
        }
        //to get the maximum similarity
        if(tempSimilarity >= maxSimilarity) {
            maxSimilarity = tempSimilarity;
            maxMember = i; //Update the member index with the max similarity
        }
    }
    //return the index of the member who has the maximum
    // similarity with the member
    return maxMember;
}

//get recommendations to the user
//recommend the member's liked and really liked books to the user
//memberAccount, bookList, memberList is the parameters
string RatingList:: getRecommendations(int memberAccount,
                                       BookList* bookList,
                                       MemberList* memberList) {
    int memberIndex = memberAccount - 1;
    //get the member who has the most similarity with the user
    int maxMemberIndex = getMostSimilarMember(memberAccount);
    int rating;
    string likedBook, reallyLikedBook, result;
    result = "You have similar taste in books as "
            + memberList->getMemberName(maxMemberIndex + 1) + "!\n\n";

    for (int j = 0; j < bookCount; j++) {
        //recommend the book that the user never read (the rating is 0)
        if (ratingArray[memberIndex][j] == 0) {
            rating = ratingArray[maxMemberIndex][j];
            if (rating == 3) {
                //get the member's liked book
                likedBook += bookList->getBookInformation(j + 1) + "\n";

            } else if (rating == 5) {
                //get the member's really liked book
                reallyLikedBook +=
                        bookList->getBookInformation(j + 1) + "\n";
            }
        }
    }
    //hold the returned string variable
    result += "Here are the books they really liked:\n" + reallyLikedBook +
            "\n" + "And here are the books they liked:\n" + likedBook;
    //return the result to display the recommendations
    return result;
}

//Check if the Ratinglist is empty
bool RatingList:: empty() const {
    if(memberCount == 0 && bookCount == 0) {
        return true;
    }
    return false;
}

//resize the row when the row capacity is full
void RatingList::resizeMember() {
    // update capacity to twice its current size
    memberCap *= 2;

    // create new array based on updated capacity
    int **tempArr = new int*[memberCap];

    // copy old array values to new array

    // for (int i = 0； i < memberCap; i ++) {
    //      tempArr[i] = new int[bookCap];
    // }
    //    for (int i = 0; i < memberCap/2; i++) {
    //        for(int j = 0; j < bookCap; j++ ) {
    //            tempArr[i][j] = ratingArray[i][j];
    //        }
    //    }

    //   // delete the 2D array ratings;
    //    for (int i = 0; i < memberCap; i++)
    //        delete [] ratingArray[i]; //deleting the inner array
    //    delete [] ratingArray; //deleting the int array
    //    ratingArray = nullptr;
    for (int i = 0; i < memberCap/2; i++) {
        tempArr[i] = ratingArray[i];
    }
    //populate the new section of the array
    for (int i = memberCap/2; i < memberCap; i++) {
        tempArr[i] = new int[bookCap];
    }

    // delete old array
    delete [] ratingArray;
    // reassign old array to new array
    ratingArray = tempArr;
}

//resize the column when the row capacity is ful
void RatingList::resizeBook() {
    // update capacity to twice its current size
    bookCap *= 2;

    // copy old array values to new array
    for (int i = 0; i < memberCap ; i++) {
        int *tempArr = new int[bookCap];
        for (int j = 0; j < bookCount; j++) {
            tempArr[j] = ratingArray[i][j];
        }
        // delete old array
        delete [] ratingArray[i];
        // reassign old array to new array
        ratingArray[i] = tempArr;
    }
}

//display information in the RatingList
string RatingList:: to_string() const {
    stringstream ss; //create an instance of stringstream class to store
    //ratingList information in the instance, then return the stored string
    for (int i = 0; i < memberCount; i++) {
        for (int j = 0; j < bookCount; j++) {
            ss << ratingArray[i][j] << " ";
        }
        ss << "\n";
    }
    return ss.str();
}


