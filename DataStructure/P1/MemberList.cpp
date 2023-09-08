// AUTHOR:   Shunuo Chen
// FILENAME: MemberList.cpp
// DATE:     10/14/2022
// PURPOSE: Implementation for MemberList described in MemberList.h

#include "MemberList.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
//Default Constructor
//Accepts capacity and creates new list on heap
MemberList::MemberList(int cap) {
    array = new Member[cap];
    capacity = cap;
}
//std::unique_ptr<MemberList> array( new MemberList(42) );
// Destructor - called automatically at end of
// program by compiler to free up memory on heap
MemberList::~MemberList() {
    delete[] array;
}

//copy object
//the constructor automatically generate a new object which
//has exactly the same thing with the original object
MemberList::MemberList(const MemberList &obj) {
    capacity = obj.capacity;
    array = new Member[capacity];
    for(int i = 0; i < obj.size(); i++) {
        Member temp = obj.array[i];
        addMember(temp.name);
    }
}

MemberList& MemberList::operator=(const MemberList &obj) {
    // check if you're assigning an object to itself
    if(this!=&obj) {
        // deallocate memory
        delete array;
        this->capacity = obj.capacity;

        // allocate memory based on new capacity
        this->array = new Member[capacity];

        // copy over elements (from obj)
        for(int i = 0; i < obj.size(); i++) {
            Member temp = obj.array[i];
            addMember(temp.name);
        }
    }
    // return object
    return *this;
}
void MemberList::addMember(string name){
    // Check that we haven't reached capacity
    if(memberCount >= capacity) {
        resize(); //only called in the implementation file
    }
    //create an instance of the member struct
    Member temp;
    temp.name = name;
    temp.account = accountId;

    // Use memberCount to access next free space in list
    array[memberCount] = temp;
    memberCount++;
    accountId++;
}
//Check if the memberList is empty
bool MemberList::empty() const {
    return memberCount == 0;
}

//get size of the memberlist
int MemberList::size() const {
    return memberCount;
}
//resize the member list when the member list is full
void MemberList::resize() {
    // update capacity to twice its current size
    capacity *= 2;

    // create new array based on updated capacity
    Member * tempArr = new Member[capacity];
    // copy old array values to new array
    for (int i = 0; i < memberCount; i++) {
        tempArr[i] = array[i];
    }
    // delete old array
    delete [] array;
    // reassign old array to new array
    array = tempArr;
}

//get member information in the member list with their account
string MemberList::getMemberName(int account) {
//create a Member array to get member name with the index(account -1)
    Member getMember = array[account-1];
    return getMember.name;
}

//display content in the memberlist
string MemberList:: to_string() const {
    stringstream ss;
    for (int i = 0; i < memberCount; i++) {
        ss << array[i].account << ", " << array[i].name << "\n";
    }
    return ss.str();
}
