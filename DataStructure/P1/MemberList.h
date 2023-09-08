// AUTHOR:   Shunuo Chen
// FILENAME: MemberList.h
// DATE:     10/14/2022
// PURPOSE: Describe the purposed and behaviors of the MemberList class, which
//          is used to store books information with an array

#ifndef P1_MEMBERLIST_H
#define P1_MEMBERLIST_H
#include <string>
using namespace std;

class MemberList {

public:
    MemberList(int); //constrcutor
    ~MemberList(); //destructor
    MemberList(const MemberList&); //copy constructor
    MemberList& operator=(const MemberList&); //overloaded =operator
    void addMember(string name); //add member to the member list
    bool empty() const; //check if the list is empty
    int size() const; //get size of the member list
    string getMemberName(int account); //pass member account to get member name
    string to_string() const; //display content in the memberlist

private:
    //create a member struct to store member information
    struct Member {
        string name; //member name
        int account; //member account
    };
    Member* array; // Pointer to the array
    int capacity; // capacity of array
    int memberCount = 0; // Number of array
    int accountId = 1; //Number of members
    void resize(); // resize array (when full
};


#endif //P1_MEMBERLIST_H
