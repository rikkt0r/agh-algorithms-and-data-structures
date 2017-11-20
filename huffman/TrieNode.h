#ifndef TRIENODE_H
#define TRIENODE_H

class TrieNode {
public:
    TrieNode(char c, int freq, TrieNode *left, TrieNode *right);
    virtual ~TrieNode();
    
    bool isLeaf();
    
    char c;
    int freq;
    TrieNode *left;
    TrieNode *right;
};

#endif /* TRIENODE_H */

