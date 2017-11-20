#include <cstdlib>
#include "TrieNode.h"

TrieNode::TrieNode(char c, int freq, TrieNode *left, TrieNode *right) {
    this->c = c;
    this->freq = freq;
    this->left = left;
    this->right = right;
}

TrieNode::~TrieNode() {
}

bool TrieNode::isLeaf() {
    return left == NULL && right == NULL;
}
