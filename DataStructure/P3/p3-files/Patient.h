// AUTHOR:   Shunuo Chen
// FILENAME: Patient.h
// DATE:     11/23/2022
// PURPOSE:  Describe the purposed and behaviors of the Patient class, which
//           is used to store patient information

#ifndef P3_PATIENT_H
#define P3_PATIENT_H
#include <string>
#include <sstream>
using namespace std;

class Patient {
public:
    Patient(int, string, string); // Constructor
    Patient(); // Constructor
    Patient(const Patient&); //copy constructor
    Patient& operator= (const Patient&); //overloaded =operator
    bool operator < (const Patient&); //overloaded < operator
    bool operator > (const Patient&); //overloaded > operator
    //pass the nextPatientNumber to set the arrival order
    void setArrivalOrder( int nextPatientNumber);
    string getPatientName() const; //get the patient name
    string getPatientInformation() const; //get the patient name, arrival
    //order and their priority code
    string to_string() const; //used to display information in the class

private:
    string name = ""; // patient's full name
    int priorityCode ; //patient's assigned priority
    string priority; //patient's assigned priority
    int arrivalOrder = 1; //assigned arrival number, start numbering at 1
};

//Default Constructor
//Accepts name, priorityCode
Patient ::Patient(int priorityCode, string name, string priority) {
    this -> priorityCode = priorityCode;
    this -> name = name;
    this -> priority = priority;
}

//Constructor
Patient:: Patient() {
}

//copy object
//the constructor automatically generate a new object which
//has exactly the same thing with the original object
Patient::Patient(const Patient &obj) {
    priorityCode = obj.priorityCode;
    name = obj.name;
    priority = obj.priority;
    arrivalOrder = obj.arrivalOrder;
}

//operator=
Patient& Patient::operator= (const Patient &obj) {
    // check if you're assigning an object to itself
    if (this != &obj) {
        priorityCode = obj.priorityCode;
        name = obj.name;
        arrivalOrder = obj.arrivalOrder;
        priority = obj.priority;
    }
    // return object
    return *this;
}

//pass the nextPatientNumber to set the arrival order
void Patient::setArrivalOrder(int nextPatientNumber) {
    arrivalOrder = nextPatientNumber;
}

//operator <
bool Patient::operator < (const Patient &right) {
    //check the priorityCode first
    if (priorityCode < right.priorityCode) {
        return true;
    }
    //if the priorityCode is the same, then compare the arrival order
    else if (priorityCode == right.priorityCode) {
        if (arrivalOrder < right.arrivalOrder) {
            return true;
        }
    }
    return false;
}
bool Patient::operator > (const Patient &right) {
    //check the priorityCode first
    if (priorityCode > right.priorityCode) {
        return true;
    }
    //if the priorityCode is the same, then compare the arrival order
    else if (priorityCode == right.priorityCode) {
        if (arrivalOrder > right.arrivalOrder) {
            return true;
        }
    }
    return false;
}

//get the patient name
string Patient::getPatientName()const {
    return name;
}

//get the patient name, priority code and the arrival order
string Patient:: getPatientInformation() const{
    string order = std ::to_string(arrivalOrder);
    stringstream ss;
    ss << "\t" << order << "\t\t  " << priority << "\t\t   " << name << endl;
    return ss.str();
}

//display information in the class
string Patient:: to_string()const {
    stringstream ss;
    ss << name << " { " << "pri=" << priority << ", " << "arrive="
        << arrivalOrder << " }";
    return ss.str();
}

#endif //P3_PATIENT_H
