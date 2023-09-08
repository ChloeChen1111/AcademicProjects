// AUTHOR:   Shunuo Chen
// FILENAME: PatientPriorityQueue.h
// DATE:     11/23/2022
// PURPOSE:  Describe the purposed and behaviors of the PatientPriorityQueue
//           class, which is used to build min heap with patient object

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H
#include <vector>
#include "Patient.h"
#include <sstream>
#include <assert.h>
using namespace std;

class PatientPriorityQueue {
public:
    PatientPriorityQueue(); //Constructor
    void add(Patient&); //Add patient to the Priority Queue
    Patient peek() const; //Peek the patient on the top of the heap
    Patient remove(); //Remove the patient on the top of the heap
    int size() const; //get size of the heap
    string to_string() const; //display information in the heap

private:
    vector<Patient> V; //Vector to store patient object
    int nextPatientNumber = 1; //initialize the nextPatientNumber to 1

    //siftup the vector when to the correct position in the heap
    void siftUp(int);
    //siftdown the vector when to the correct position in the heap
    void siftDown(int);
    //get the parent slot index
    int getParent(int) const;
    //get the left child slot index
    int getLeftChild(int) const;
    //get the right child slot index
    int getRightChild(int) const;
    //check if the heap is empty
    bool empty() const;
};

//constructor
PatientPriorityQueue::PatientPriorityQueue() {
}

//add patient to the heap
//accepting patient object
void PatientPriorityQueue::add(Patient& patient) {
    //set the arrival order of patient
    //then increment the next patient number
    patient.setArrivalOrder(nextPatientNumber++);
    //add patient to the vector
    V.push_back(patient);

    siftUp(V.size() - 1);
}

//get the first patient in the list
Patient PatientPriorityQueue::peek() const {
    assert(!empty());
    return V[0];
}
//remove patient in the list
Patient PatientPriorityQueue::remove() {
    assert(!empty());
    //hold the patient needed to return
    Patient result = V[0];
    //to get the correct index, not beyond boundary
    //and swap the V at index 0 with the last one in the heap
    V[0]= V[V.size()-1];
    //decrement the size of the vector to delete the last patient in the vector
    V.resize(V.size()-1);
    //stop sift down when the Vector's size is less than 1
    if(V.size() > 1)
        siftDown(0);
    //return the patient need to remove
    return result;
}

void PatientPriorityQueue::siftUp(int index) {
    //hold variable to get the parent index
    int parentIdx;
    //build a min heap
    if (index != 0) {
        //get the parent index in the heap
        parentIdx = getParent(index);
        //compare the added patient with the patient at the parent index
        if(V[parentIdx] > V[index]) {
            //swap the parent patient with the new added patient
            Patient temp = V[parentIdx];
            V[parentIdx] = V[index];
            V[index] = temp;
            //stop swapping when the parent is less than the new patient or
            //get the root of the heap
            siftUp(parentIdx);
        }
    }
}

void PatientPriorityQueue::siftDown(int index) {
    int leftIdx, rightIdx, minIdx;
    //get the left child index
    leftIdx = getLeftChild(index);
    //get the right child index
    rightIdx = getRightChild(index);

    if(rightIdx >= size()) {
        if(leftIdx >= size()) {
            return;
        }
        else {
            //if no right child, just left child. compare with the left child
            minIdx = leftIdx;
        }
    } else {
        //if there is a right child, compare with right child
        //find the max value from the children
        if(V[leftIdx] < V[rightIdx])
            minIdx = leftIdx;
        else {
            minIdx = rightIdx;
        }
    }
    //when the vector at index is greater than the vector at the min index
    if(V[index] > V[minIdx] ) {
        //swap the vector at index and the vector at the min index
        Patient temp = V[minIdx];
        V[minIdx] = V[index];
        V[index] = temp;
        //sift down the vector with patient until it get correct position
        siftDown(minIdx);
    }
}

//get the parent index in the heap
//accepting index of the new added patient
int PatientPriorityQueue::getParent(int index) const {
    return (index - 1) / 2;
}

//get the left child index in the heap
//accepting index of the root patient
int PatientPriorityQueue::getLeftChild(int index) const {
    return 2 * index + 1;
}

//get the right child index in the heap
//accepting index of the root patient
int PatientPriorityQueue::getRightChild(int index) const {
    return 2 * index + 2;
}

//check if the heap is empty
bool PatientPriorityQueue:: empty() const {
    return size() == 0;
}

//get the size of the heap
int PatientPriorityQueue:: size() const {
    return V.size();
}

//display information in the heap
string PatientPriorityQueue ::to_string() const {
    stringstream ss;
    //keep i and V.size the same data type
    for (int i = 0; i < (int)V.size(); i++) {
        ss << V[i].getPatientInformation();
    }
    //ss << "\n";
    return ss.str();
}

#endif //P3_PATIENTPRIORITYQUEUE_H
