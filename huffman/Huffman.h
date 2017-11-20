#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <cstdlib>
#include <queue>
#include <string>

#include <iostream>

#include "BinaryFileHandler.h"
#include "TrieNode.h"


using std::string;

class Huffman {
public:
    Huffman();
    virtual ~Huffman();
    
    void decode(string fileEncoded, string fileCode, string fileDecoded);
    void encode(string fileInput, string fileCode, string fileEncoded);
    void decodeParallel(string fileEncoded, string fileCode, string fileDecoded);
    void encodeParallel(string fileInput, string fileCode, string fileEncoded);
    
private:
    const int R = 256;
    
    TrieNode* readTrie(BinaryFileHandler *reader);
    void writeTrie(BinaryFileHandler *writter);
    void writeTrie(TrieNode *x, BinaryFileHandler *writter);
    void buildTrie(int freq[]);
    string buildCode(TrieNode *root);
    void buildCode(string st[], TrieNode *x, string s);
    
    TrieNode *root;
};

#endif /* HUFFMAN_H */

