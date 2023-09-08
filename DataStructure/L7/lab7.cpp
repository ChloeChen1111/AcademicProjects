// AUTHOR:   Shunuo Chen
// FILENAME: lab7.cpp
// DATE:     11/24/2022
// PURPOSE:  This program prompts the user to enter an input filename and an
//           output file name;
//           We read the files and store letters in the file to a BST node
//           with the letter's frequency and its encoding. Thus, we could build
//           a priority queue tree based on letter's frequency. Then, we build a
//           huffman tree according to the priority queue to encode the input
//           file. Then taking the huffman tree and the encoding of each letter
//           we decode the tree to get the string.
// INPUT:    User input of input filename which they want to encode the file.
//           and the output filename to store the encoded file
// PROCESS:  Read the input file, build a huffman tree to encode the file,
//           then put the encoding to the
//           output file. Using the encoding and huffman tree to decode the file
// OUTPUT:   display information stored in the huffman tree and decode the
//           encoding of each node to see the stored letter

//Analysis: When different letters' frequency in a file have big difference, the
// huffman code will be efficient. Otherwise, it will not be efficient.
// for example: when the letter a's frequency is 2, and letter b's frequency is
// 90, huffman code will be efficient. However, if both letter a and b has the
// same frequency, it will not be as efficient as the last case
#include "Huffman.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char * argv[])
{
    HuffmanTree hc;
    string inputFile, outputFile;
    //get the input file name
    cout << "Please enter the input filename: ";
    cin >> inputFile;
    //get the output file name
    cout << "Please enter the output file: ";
    cin >> outputFile;

    // create code tree
    hc.createCodeTree(inputFile);

    // encode file
    hc.encodeFile(inputFile, outputFile);

    // decode file
    hc.decodeFile(outputFile);

    // print
    cout << hc;
    return 0;
}
