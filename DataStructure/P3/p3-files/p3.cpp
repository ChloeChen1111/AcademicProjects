// AUTHOR:   Shunuo Chen
// FILENAME: p3.cpp
// DATE:     11/23/2022
// PURPOSE:  The program creates a triage room to serve patients
// INPUT:    User input of commands.txt. Add patients in the file to the triage
//           system
// PROCESS:  The program allows nursers to put patients' information to
//           the triage system. Patients get service based on their priority
//           code and arrival order.The system will display the function manu
//           with help command. Nursers can add patients and remove
//           patients to the triage room. They can also see the list of
//           patients in the room and check the next patient will be served.
//           The program can load input file and read from the file then add
//           patients to the triage room
// OUTPUT:   Display manu of the system. Waiting patients in the triage room.
//           as well as the next patients need to be served

// TODO: add functional documentation (and inline comments, as necessary)

#include "PatientPriorityQueue.h"
#include "Patient.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//hole the variable needed to be removed
const string WHITESPACE = " \n\r\t\f\v";

void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.

string removeSpace(string);
//remove whitespace in the head and tail of the patients' names

int main() {
	// declare variables
	string line;

	// welcome message
	welcome();

	// process commands
	PatientPriorityQueue priQueue;

    //control the do while loop starts when the user has input
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));

	// goodbye message
	goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
	// get command from the input string
	string cmd = delimitBySpace(line);
	if (cmd.length() == 0) {
        //display error message when return false when there is no command
		cout << "Error: no command given.";
		return false;
	}
	// process user input
	if (cmd == "help")
		help();
	else if (cmd == "add")
		addPatientCmd(line, priQueue);
	else if (cmd == "peek")
		peekNextCmd(priQueue);
	else if (cmd == "next")
		removePatientCmd(priQueue);
	else if (cmd == "list")
		showPatientListCmd(priQueue);
	else if (cmd == "load")
		execCommandsFromFileCmd(line, priQueue);
	else if (cmd == "quit")
		return false;
	else
		cout << "Error: unrecognized command: " << cmd << endl;
	return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {
	string priority;
    //get the prioity code in the line
	priority = delimitBySpace(line);
    //get the name with potential whitespace
    string unprocessed_name = line;
    //remove the leading and trailing space in the name
    string name = removeSpace(unprocessed_name);

   //check if the priority code is empty
	if (priority.length() == 0) {
		cout << "Error: no priority code given.\n";
		return;
	}
    //check if the name is empty
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    int priorityCode = 0;
    if (priority.compare("immediate") == 0 ) {
        //when priority is immediate, add 0 as priority code to the patient
        priorityCode = 0;
        Patient patient(priorityCode, name, priority);
        priQueue.add(patient);
        cout << "Added patient "<<'"'
            << name << '"' <<  " to the priority system\n";
    } else if (priority.compare("emergency") == 0 ) {
        //when priority is emergency, add 15 as priority code to the patient
        priorityCode = 15;
        Patient patient(priorityCode, name, priority);
        priQueue.add(patient);
        cout << "Added patient "<<'"'
             << name << '"' <<  " to the priority system\n";
    } else if (priority.compare("urgent") == 0) {
        priorityCode = 30;
        //when priority is urgent, add 30 as priority code to the patient
        Patient patient(priorityCode, name, "urgent   ");
        priQueue.add(patient);
        cout << "Added patient "<<'"'
             << name << '"' <<  " to the priority system\n";
    } else if (priority.compare("minimal") == 0) {
        priorityCode = 120;
        //when priority is minimal, add 120 as priority code to the patient
        Patient patient(priorityCode, name, "minimal  ");
        priQueue.add(patient);
        cout << "Added patient "<<'"'
             << name << '"' <<  " to the priority system\n";
    } else {
        //display error message when the input is not validate
        cout << "Error: invalidate priority code: " << priority << endl;
    }
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
	// TODO: shows next patient to be seen
   Patient result = priQueue.peek();
   cout << "Highest priority patient to be called next: ";

   cout << result.getPatientName() << endl;
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
    // TODO: removes and shows next patient to be seen
    Patient result = priQueue.remove();
    cout << "This patient will now be seen: ";
    cout << result.getPatientName() << endl;
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
	cout << "# patients waiting: " << priQueue.size() << endl << endl;
	cout << "  Arrival #   Priority Code   Patient Name\n"
		  << "+-----------+---------------+--------------+\n";
	// TODO: shows patient detail in heap order
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line;
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}

string delimitBySpace(string &s) {
	unsigned pos = 0; //initialize pos at 0
	char delimiter = ' '; //hold the char need to split the string
    //initialize the result as s, not " "  in case input space after command
	string result = s; //hold the returned variable
    //s.substr(start point, how many chars)
    //"add minimal Chloe Chen"
	pos = s.find(delimiter); //get the pos of the delimiter
	if (pos != string::npos) {
        //hold the string before the delimiter pos to return
		result = s.substr(0, pos);
        //erase the string before the delimiter and the delimiter
		s.erase(0, pos + 1);
	}
    return result;
	//return (result == "") ? s : result;
}

string removeSpace(string name) {
    //before trim the left whitespace
    //unsigned integers can only be positive
    unsigned int start = name.find_first_not_of(WHITESPACE);
    //get the string from the start index to the end of the whole string
    string ltrim = (start == std::string::npos) ? "" : name.substr(start);
    //after removing the left whitespaces, remove the right whitespaces
    unsigned int end = ltrim.find_last_not_of(WHITESPACE);
    // substr(start index, length)
    string rtrim = (end == std::string::npos) ? "" : ltrim.substr(0, end + 1);
    //return the string without any extra space (heading and trailing)
    return rtrim;
}

void welcome() {
	// TODO
    cout << "Welcome to the triage program!" << endl
         << "You can add patients with their name and priority code "
            "to the system" << endl;
}

void goodbye() {
	// TODO
    cout << "\nThank you for using the program, goodbye!" << endl;

}	

void help() {
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}
