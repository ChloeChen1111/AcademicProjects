// AUTHOR:   Shunuo Chen
// FILENAME: HuffmanTree.cpp
// DATE:     11/24/2022
// PURPOSE: Implementation for HuffmanTree described in HuffmanTree.h

#include "Huffman.h"
#include <sstream>

//create a huffman tree
//Accepts filename
bool HuffmanTree::createCodeTree(string filename) {

    std::priority_queue<
            BST<CharFreq>::BSTNode*,
            std::vector<BST<CharFreq>::BSTNode*>,
            BST<CharFreq>::FrequencyCompare
    > myPriorityQ;
    string str;
    string allText = "";
    //make sure we can open the inputfile
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()) {
        cout << "ERROR loading file!\n";
        return false;
    }

    while (!infile.eof()) {    // To get you all the lines.
        getline(infile,str); // Saves the line in STRING.
        //stores all the input string at allText
        allText += str + "\n";
    }
    infile.close();

    const int SIZE = 256;
    CharFreq array[SIZE]; //create an array to hold CharFreq type data
    //loop through all the char in the string
    for (int i = 0; i < (int)allText.length(); i++) {
        char letter = allText[i]; //get the char at the i index of the string
        //use the ASCII value of char as the index of the array
        // to store the char
        array[int(letter)].letter = letter;
        //increment frequency of the char and store the attribute in the array
        array[int(letter)].frequency++;
    }

    //Loop through all characters in array and create a node while data is a cf
    //data type
    for (int i = 0; i < SIZE; i++) {
        BST<CharFreq>:: BSTNode *b = new BSTNode(array[i]);
        myPriorityQ.push(b); //push the node to the min heap
    }
    //pop all the node with 0 frequency
    //stop pop the heap until the size of the heap is 0
    while(myPriorityQ.size() > 0 && myPriorityQ.top()->data.frequency == 0){
        myPriorityQ.pop();
    }

    //remove 2 nodes from the BST and create a new node with the 2 nodes
    while(myPriorityQ.size() > 1){
        BST<CharFreq>:: BSTNode * leftChild = myPriorityQ.top();
        myPriorityQ.pop();

        BST<CharFreq>:: BSTNode * rightChild = myPriorityQ.top();
        myPriorityQ.pop();

        //create a new node as parent node with sum of left child frequency and
        // right child frequency as frequency
        CharFreq * cf =  new CharFreq();
        BST<CharFreq>::BSTNode* parentNode = new BSTNode(*cf);

        parentNode->data.frequency =
                leftChild->data.frequency + rightChild->data.frequency;
        parentNode->left = leftChild;
        parentNode->right = rightChild;

        //add back the parent node to the heap
        myPriorityQ.push(parentNode);
    }

    //set root to the last node
    root = myPriorityQ.top();

    //encode each node in the tree
    //traverse the tree and get the huffman code of node until get the leaf node
    //set the encoding to the CharFreq array.
    encodeNode(root, "");
    return true;
}

//Accept character at the node and get a string of the character
string HuffmanTree::encoding(unsigned int character) {
    if (character >= 33 && character <= 126)
        return string(1, character);
    else if (character >= 128 && character <= 254)
        return "EON"; // extended ASCII or non-ASCII
    switch(character) {
        case   0: return "NUL";   break;
        case   1: return "SOH";   break;
        case   2: return "STX";   break;
        case   3: return "ETX";   break;
        case   4: return "EOT";   break;
        case   5: return "ENQ";   break;
        case   6: return "ACK";   break;
        case   7: return "BEL";   break;
        case   8: return "BS";    break;
        case   9: return "TAB";   break;
        case  10: return "LF";    break;
        case  11: return "VT";    break;
        case  12: return "FF";    break;
        case  13: return "CR";    break;
        case  14: return "SO";    break;
        case  15: return "SI";    break;
        case  16: return "DLE";   break;
        case  17: return "DC1";   break;
        case  18: return "DC2";   break;
        case  19: return "DC3";   break;
        case  20: return "DC4";   break;
        case  21: return "NAK";   break;
        case  22: return "SYN";   break;
        case  23: return "ETB";   break;
        case  24: return "CAN";   break;
        case  25: return "EM";    break;
        case  26: return "SUB";   break;
        case  27: return "ESC";   break;
        case  28: return "FS";    break;
        case  29: return "GS";    break;
        case  30: return "RS";    break;
        case  31: return "US";    break;
        case  32: return "SPC";   break;
        case 127: return "DEL";   break;
        case 255: return "BLANK"; break;

        default: return "UNKNOWN";
    }
}

//Accept the root of the tree and a string of encoding
//add the encoding of each character to the node
void HuffmanTree::  encodeNode(BSTNode *root, string encoding) {
    // when the root node has no child
    // get the leaf node
    if(root->left == nullptr && root->right == nullptr) {
        //add encoding of each char to the node
        root->data.encoding = encoding;
        return;
    }
    //find the left child tree and add 0 to the encoding
    encodeNode(root->left, encoding + "0");
    //find the right child tree and add 1 to the encoding
    encodeNode(root->right, encoding + "1");
    return;
}
//Accept the char and root of the huffman tree
//get the encoding of a specific char
string HuffmanTree:: findEncoding(BSTNode *root, char letter){
    //once we get the leaf node, check if the letter is the target letter
    //once we find the target letter return encoding of the letter
    //if we cannot find the target letter, return a empty string
    if (root->left == nullptr && root->right == nullptr) {
        return (root->data.letter == letter) ? root->data.encoding : "";
    }
    //find the left and right subtree
    return findEncoding(root->left, letter) + findEncoding(root->right, letter);
}

//Accepting the input and output file name
//encode each letter in the file with the huffman code
bool HuffmanTree::encodeFile(string originalFilename, string outputFilename) {
    string str;
    string allText = "", currentStream = "";
    ifstream infile;
    const int WRITE_SIZE = 8;
    //make sure open the inputfile
    infile.open(originalFilename.c_str());
    if( !infile.is_open() ) {
        cout << "ERROR loading file!\n";
        return false;
    }
    while (!infile.eof()) {        // To get you all the lines.
        getline(infile, str);   // Saves the line in string.
        allText += str + "\n";
    }
    infile.close();
    //make sure open the output file
    std::ofstream outStream(outputFilename.c_str(), std::ios::binary);
    if (!outStream.is_open()) {
        cout << "ERROR creating output file!\n";
        return false;
    }
    for (int i = 0; i < (int)allText.length(); i++) {
        // TODO: encodeFile - add your code here
        //  add the appropriate encoding for allText[i] to currentStream
        //get the encoding of each char
        string encoding = findEncoding(HuffmanTree::root, (char)allText[i]);
        //store all encodings of the chars
        currentStream += encoding;

        while ((int)currentStream.length() > WRITE_SIZE) {
            string byte = currentStream.substr(0, WRITE_SIZE);
            bitset<8> set(byte);
            const char toWrite = (unsigned char)((unsigned int)set.to_ulong());
            outStream.write(&toWrite,sizeof(char));
            currentStream = currentStream.substr(WRITE_SIZE,
                                  currentStream.length() - WRITE_SIZE);
        }
    }
    outStream.close();
    return false;
}

//Accepting the input file name
//Using huffman code to get the string
bool HuffmanTree::decodeFile(string filename) {
    int i = 0; string bitStream = "";
    ifstream encodedfile;
    //make sure the file can be opened
    encodedfile.open(filename.c_str(), ios::binary);
    if (!encodedfile.is_open()) {
        cout << "ERROR opening encoded file!\n";
        return false;
    }
    encodedfile >> std::noskipws;
    while (!encodedfile.eof()) {
        unsigned char readMe;
        encodedfile >> readMe;
        bitset<8> set((unsigned long)readMe);
        bitStream += set.to_string();
    }
    encodedfile.close();
    bitStream.erase(bitStream.length()-8, 8); // remove duplicated final byte
    while (i != -1)
        i = traverseAndPrint(bitStream, i);
    return false;
}
//Accepting huffman code stored in the bits, and index i, the tree root
//traverse the bit and display the string
int HuffmanTree::traverseAndPrint(string &bits, int i, BSTNode *cur) {
    //when the index i beyond the length of bit, return -1
    if(i >= (int)bits.length())
        return -1;
    //when the root is nullptr, return -1
    if(cur == nullptr) {
        return -1;
    }
    //when we get the leaf node, print the letter at the node
    if (cur->data.letter != '\0'){
        //display the text
        setbuf(stdout, 0);
        cout << cur->data.letter;
        //start traverse the tree from root
        return i;
    }
        //when the bits at index i stores value of 0, we get into the left
        // subtree to find a leaf node and check the next index of the bit
    else if (bits[i] == '0'){
        return traverseAndPrint(bits, i+1, cur->left);
    }else if (bits[i] == '1'){
        //when the bits at index i stores value of 1, we get into the right
        // subtree to find a leaf node and check the next index of the bit
        return traverseAndPrint(bits, i+1, cur->right);
    }
    return -1;
}
//Accepting the output
//call the helper function to
//display frequency and encoding of each node
void HuffmanTree::displayCode(ostream &out) {
    cout <<"\n\n**********************************"
           "*************************************************" <<endl;
    cout <<"*                       Huffman Tree Character Encoding Map                      "
           " *" <<endl;
    cout <<"*                 (EON == Extended ASCII Or Non-ASCII Character)                "
           "  *" <<endl;
    cout <<"****************************************"
           "*******************************************" <<endl;
    //call the helper function and pass the tree's root as parameter
    cout << displayCodeHelper(root) << endl;
}
//Accepting
string HuffmanTree:: displayCodeHelper(BSTNode *root) {

    //BSTNode * ptr = root;
    //if we get the leaf node, display character at the node
    if(root->left == nullptr && root->right == nullptr) {

        return "Character: " + encoding(root->data.letter)  + "\t\t" +
               "ASCII: " + to_string((unsigned int)root->data.letter) + "\t\t"
                "Frequency: " + to_string((int)root->data.frequency)
                + "\t\t""Encoding: " + root->data.encoding + "\n";
    }
    //find both the left and right subtree
    return displayCodeHelper(root->left) + displayCodeHelper(root->right);
}

ostream& operator<<(ostream &out, HuffmanTree &code) {
    code.displayCode(out);
    return out;
}
