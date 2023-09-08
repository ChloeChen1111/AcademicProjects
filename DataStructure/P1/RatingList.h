// AUTHOR:   Shunuo Chen
// FILENAME: RatingList.h
// DATE:     10/14/2022
// PURPOSE: Describe the purposed and behaviors of the RatingList class, which
//          is used to store books information with an array
#ifndef P1_RATINGLIST_H
#define P1_RATINGLIST_H
#include <string>
#include "MemberList.h"
#include "BookList.h"

using namespace std;

class RatingList {
public:
    RatingList(int, int); // Constructor accepts initial capacity of list
    ~RatingList(); // Destructor - Used to free up memory on heap
    RatingList(const RatingList&); //copy constructor, used to copy the BookList
                                    //object
    RatingList& operator=(const RatingList&); //overloaded =operator
    void updateRating(int, int, int); // member index, book index, rating
    void addMember(); //addMember to update the number of member in the list
    void addBook(); //addBook to update the number of member in the list
    bool empty() const; // determines if list is empty or not
    int getMemberSize() const; //get the number of member in the list
    int getBookSize() const; //get the number of book in the list
    string viewMemberRatings(int, string, BookList*); //To view all ratings of a
                //member, pass in ccountId, memberName, BookList object
    string getRecommendations(int, BookList*, MemberList*);//get recommendations
        //to a member with passed in original member index, BookList object
    int getRating(int, int); //get ratings of a specific member and a
                            // specific book
    string to_string() const; //display content in the rating list

private:
    int memberCap; // row capacity of array
    int bookCap; //column capacity of array
    int **ratingArray; // pointer to the 2D array
    int memberCount; //Number of array row
    int bookCount; //Number of array column
    int getMostSimilarMember(int);
    void resizeMember(); //resize the row capacity
    void resizeBook(); //resize the column capacity
};

#endif //P1_RATINGLIST_H
