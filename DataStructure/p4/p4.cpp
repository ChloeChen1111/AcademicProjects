// AUTHOR:   Shunuo Chen
// FILENAME: p4.cpp
// DATE:     10/14/2022
// PURPOSE:  This program prompts the user to input files;
//           We read the files and get each word from the file, and store them
//           in the array of linkedlist. Then, we clean the common words in the
//           input file. Then we calculate each word count.
//           Then display the total word statistics, unique word statistics, and
//           load factor
// INPUT:    User input files they want to get the word count
// PROCESS:  Read the input file store information in the file in an array
//           of linkedlist. Then clean common words in the file, and remove
//           these words from word count. Then calculate the total word count,
//           unique word count, and loaded factor of the array.
// OUTPUT:   display the total word statistics, unique word statistics, and
//           load factor

#include "WordCounter.h"
#include "CommonWordList.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//display word count from the input file
void displayWordCount();

//Clean word from the input file
//return the clean string
//Accepting input file
string cleanWord(string);

//Remove the common words from the input file
//Accepting WordCounter object
void removeCommonWords(WordCounter &);

const char APOSTROPHE_CHAR = '\''; 	// apostrophe character used in cleanWord
const char HYPHEN_CHAR = '-'; 		// hyphen/dash character used in cleanWord

int main() {
    //call the displayWordCount function
    displayWordCount();
}

void displayWordCount() {
    ifstream inFile;
    string filename;
    int capacity;
    //get the filename from the user
    cout << "What is the filename: ";
    //read the file name
    getline(cin, filename);

    //get the capacity from the user
    cout <<"What is the capacity: ";
    cin >> capacity;
    //create a WordCounter instance
    WordCounter wc(capacity);

    string line, singleWord;
    //open the file
    inFile.open(filename);
    //verify the file is opened
    if(inFile.is_open()) {
        //read each line in the file and store text into stringstream ss
        while(getline(inFile,line)) {
            stringstream ss;
            ss << line;
            //get each word in the input file
            while(getline(ss, singleWord, ' ')) {
                //clean words from input file
                string cleanedWord = cleanWord(singleWord);
                //check if the cleaned word is empty, add non-empty word to the
                //WordCounter linkedlist
                if(cleanedWord.length() != 0) {
                    wc.addWord(cleanedWord);
                }
            }
        }
        // populate common words
        CommonWordList::populateWords();
        //remove the common words
        removeCommonWords(wc);

        //display the Word Counter statistics:
        cout << "\nWord Counter statistics: \n" <<
             "  #Unique   #Total   Load Factor\n" <<
             "+---------+--------+---------+" << endl;
        printf (" %6d", wc.getUniqueWordCount());

        printf (" %8d", wc.getTotalWordCount());
        //calculate the load factor and print it
        float factor = static_cast <float>
                       (wc.getUniqueWordCount())/static_cast <float> (wc.getCapacity());
        printf("%12.3f\n", factor);

        stringstream ss2;
        string analysisWord, analysisLine;
        cin.ignore(); //need to remove new line to getline operator
        //prompt user to enter words they want to delete
        cout << "\nEnter words (separated by space): ";
        //store the input string in analysisLine
        getline(cin, analysisLine);
        //store analysisLine into the stringstream ss2
        ss2 << analysisLine;
        cout << "\nAnalysis of words: \n" <<
             "  Given Word   Count\n" <<
             "+------------+-------+" << endl;
        //get each word in the line split by space
        while(getline(ss2, analysisWord, ' ')) {
            printf (" %6s", analysisWord.c_str());
            printf("%12d\n", wc.getWordCount(analysisWord));

        }
        stringstream ss3;
        string removeLine, removeWord;
        //prompt users to enter words they want to remove
        cout << "\nRemove the following words: ";
        getline(cin, removeLine);
        //store the removeLine string into ss3
        ss3 << removeLine;
        cout << "\nWord Counter statistics: \n" <<
             "  #Unique   #Total   Load Factor\n" <<
             "+---------+--------+---------+" << endl;
        //get each word the user want to remove split by space
        while(getline(ss3, removeWord, ' ')) {
            //call the remove function to remove the word
            wc.removeWord(removeWord);
        }
        printf (" %6d", wc.getUniqueWordCount());
        printf (" %8d", wc.getTotalWordCount());
        //calculate the new load factor based on updated word count
        float newFactor = static_cast <float>
                          (wc.getUniqueWordCount())/static_cast <float> (wc.getCapacity());
        printf("%12.3f\n", newFactor);
    }
    else  {
        cout << "The file you entered cannot be opened";
    }
    inFile.close();
}


string cleanWord(string s) {
   string result = "";                  // Keep track of the cleaned result.
   unsigned i = 0, length = s.length(); // Input for the for loop.
   for (; i < length; i++) {
      if (isalnum(s[i])) 
         result += tolower(s[i]);
      else if (s[i] == APOSTROPHE_CHAR) {
         if (i > 0 && isalnum(s[i-1]))
            result += s[i];
      } else if (s[i] == HYPHEN_CHAR) {
         if (i > 0 && i < (length-1) && isalnum(s[i-1]) && isalnum(s[i+1]))
            result += s[i];
			// If a word ends in a hyphen, we assume it is residue that needs to
			// be paired with the next word. Return the word with the hyphen as a
			// signal to the caller to retain it as residue.
         else if (i > 0 && i == (length-1) && isalnum(s[i-1]))
            result += s[i];
      }
   }
   return result;
}

void removeCommonWords(WordCounter &wc) {
   for (string &s : CommonWordList::getWords())
      wc.removeWord(s);
}
