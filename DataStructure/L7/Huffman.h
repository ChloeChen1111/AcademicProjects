// AUTHOR:   Shunuo Chen
// FILENAME: HuffmanTree.h
// DATE:     11/24/2022
// PURPOSE:  Describe the purposed and behaviors of the HuffmanTree class, which
//           is used to store Huffman tree information with nodes

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <bitset>
#include "BST.h"

using namespace std;

class CharFreq {
public:
    //default constructor
    CharFreq() : letter('\0'), frequency(0), encoding("") { }
    //overloaded constructor
    CharFreq(unsigned char l, float f) :letter(l), frequency(f), encoding("") {
    }
    //attributes of the CharFreq class
    unsigned char letter;
    float frequency;
    string encoding;

    //overloaded operator
    bool operator>(const CharFreq &rhs) const {
        return frequency > rhs.frequency;
    }
};

//HuffmanTree inherent the BST Class
class HuffmanTree : BST<CharFreq> {
public:
    HuffmanTree() {} //constructor
    bool createCodeTree(string filename);
    //compress the file to the huffman code
    bool encodeFile(string originalFilename, string outputFilename);
    //decode the file with Huffman tree
    bool decodeFile(string filename);
    //display the huffman code in each node
    void displayCode(ostream &out);
private:
    //find encoding of each letter
    string findEncoding(BSTNode *root, char letter);
    //accepting root of the huffman tree to display code of each letter
    string displayCodeHelper(BSTNode *root);
    //Accept character at the node and get a string of the character
    string encoding(unsigned int );
    //take the huffman code and the index of the bit
    //to get information stored in the tree
    inline int traverseAndPrint(string &bits, int i) {
        return traverseAndPrint(bits, i, root);
    }
    //get encoding of each node
    void encodeNode(BSTNode *root, string encoding);
    //traverse the huffman tree and get information stored in the tree
    int traverseAndPrint(string &bits, int i, BSTNode *cur);
};

ostream& operator<<(ostream &out, HuffmanTree &code);

#endif 
