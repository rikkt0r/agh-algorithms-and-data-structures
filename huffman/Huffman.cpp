#include <omp.h>
#include "Huffman.h"

#define READ_MODE false
#define WRITE_MODE true

using std::string;
using std::cerr;
using std::endl;

struct CompareFrequency {
    bool operator()(TrieNode *t1, TrieNode *t2) {
        return t1->freq > t2->freq;
    }
};

Huffman::Huffman() {}
Huffman::~Huffman() {}

void Huffman::decode(string fileEncoded, string fileCode, string fileDecoded){
    BinaryFileHandler *reader = new BinaryFileHandler(fileCode, READ_MODE);
    BinaryFileHandler *r = new BinaryFileHandler(fileEncoded, READ_MODE);
    BinaryFileHandler *w = new BinaryFileHandler(fileDecoded, WRITE_MODE);
    
    TrieNode *root = this->readTrie(reader);
    int N = r->readInt();
    
    for(int i=0; i<N; i++){
        TrieNode *x = root;
        while(!x->isLeaf()){
            if(r->readBool())
                x = x->right;
            else
                x = x->left;
        }
        w->write(x->c);
    }
}

void Huffman::encode(string fileInput, string fileCode, string fileEncoded){
    
    //wczytanie calosci do pamieci
    BinaryFileHandler *reader = new BinaryFileHandler(fileInput, READ_MODE);
    string tmp_s = reader->readAll();
    int inputSize = tmp_s.length();
    const char *input = tmp_s.c_str();
    
    // czestosc wystepowania ASCII
    int freq[this->R];
    for(int i=0; i< R; i++)
        freq[i] = 0;
    for(int i=0; i< inputSize; i++)
        freq[input[i]]++;
    
    // drzewo trie
    this->buildTrie(freq);
   
    // tablica kodow
    string codeArr[R];
    this->buildCode(codeArr, this->root, "");
    
    cerr << "len: " << inputSize << endl;
    for(int i=0; i<R; i++){
        if(!codeArr[i].empty())
            cerr << (char)i << ": " << codeArr[i] << endl;
    }
    
    // zapis tablicy kodowej
    BinaryFileHandler *codeWritter = new BinaryFileHandler(fileCode, WRITE_MODE);
    this->writeTrie(codeWritter);
    
    // zapis dlugosci ciagu
    BinaryFileHandler *writter = new BinaryFileHandler(fileEncoded, WRITE_MODE);
    writter->writeBin(inputSize);
    
    // zapis ciagu
    for(int i=0; i < inputSize; i++){
        string code = codeArr[input[i]];
        for(int j=0; j < code.length(); j++){
            if(code[j] == '1')
                writter->writeBin(true);
            else
                writter->writeBin(false);
        }
    }
    

//    string data = "";
//    
//    for(int i=0; i < inputSize; i++){
//        string code = codeArr[input[i]];
//        for(int j=0; j < code.length(); j++){
//            if(code[j] == '1')
//                data += '1';
//            else
//                data += '0';
//        }
//    }
//    
//    //cerr << "data: " << data << endl;
//    writter->write(data);
    
    delete reader;
    delete codeWritter;
    delete writter;
}
void Huffman::decodeParallel(string fileEncoded, string fileCode, string fileDecoded){
    BinaryFileHandler *reader = new BinaryFileHandler(fileCode, READ_MODE);
    BinaryFileHandler *r = new BinaryFileHandler(fileEncoded, READ_MODE);
    BinaryFileHandler *w = new BinaryFileHandler(fileDecoded, WRITE_MODE);
    
    TrieNode *root = this->readTrie(reader);
    int N = r->readInt();
    
    const int maxThreads = omp_get_max_threads();
    
    for(int i=0; i<N; i++){
        TrieNode *x = root;
        while(!x->isLeaf()){
            if(r->readBool())
                x = x->right;
            else
                x = x->left;
        }
        w->write(x->c);
    }

}
void Huffman::encodeParallel(string fileInput, string fileCode, string fileEncoded){
    //wczytanie calosci do pamieci
    BinaryFileHandler *reader = new BinaryFileHandler(fileInput, READ_MODE);
    string tmp_s = reader->readAll();
    int inputSize = tmp_s.length();
    const char *input = tmp_s.c_str();
    const int maxThreads = omp_get_max_threads();
    
    // czestosc wystepowania ASCII
    int freq[this->R];
    for(int i=0; i< R; i++)
        freq[i] = 0;
    for(int i=0; i< inputSize; i++)
        freq[input[i]]++;
    
    // drzewo trie
    this->buildTrie(freq);
   
    // tablica kodow
    string codeArr[R];
    this->buildCode(codeArr, this->root, "");
    
    cerr << "len: " << inputSize << endl;
    for(int i=0; i<R; i++){
        if(!codeArr[i].empty())
            cerr << (char)i << ": " << codeArr[i] << endl;
    }
    
    // zapis tablicy kodowej
    BinaryFileHandler *codeWritter = new BinaryFileHandler(fileCode, WRITE_MODE);
    this->writeTrie(codeWritter);
    
    // zapis dlugosci ciagu
    BinaryFileHandler *writter = new BinaryFileHandler(fileEncoded, WRITE_MODE);
    writter->writeBin(inputSize);

    // zapis ciagu
    string data[maxThreads];
    string dataToWrite = "";
    
    for (int i = 0; i< maxThreads; i++) {
        data[i] = "";
    }

    #pragma omp parallel shared(codeArr, input)
    {
        int numThread = omp_get_thread_num();
        for (int i = numThread * inputSize/maxThreads; i < (numThread+1)*inputSize/maxThreads; i++) {
            string code = codeArr[input[i]];
            for(int j=0; j < code.length(); j++){
                if(code[j] == '1')
                    data[numThread] += '1';
                else
                    data[numThread] += '0';
            }
        }
    }

    
    for (int i = 0; i< maxThreads; i++) {
        dataToWrite += data[i];
    }
    
    //cerr << "data: " << dataToWrite << endl;
    
    writter->write(dataToWrite);
    
    delete reader;
    delete codeWritter;
    delete writter;
}

TrieNode* Huffman::readTrie(BinaryFileHandler *r){
    if (r->readBool())
        return new TrieNode(r->readChar(), 0, NULL, NULL);
    return new TrieNode('\0', 0, readTrie(r), readTrie(r));
}

void Huffman::writeTrie(BinaryFileHandler *w){
    writeTrie(this->root, w);
}

void Huffman::writeTrie(TrieNode *x, BinaryFileHandler *w){
    if(x->isLeaf()){
        w->writeBin(true);
        w->writeBin(x->c);
        return;
    }
    w->writeBin(false);
    writeTrie(x->left, w);
    writeTrie(x->right, w);
}

void Huffman::buildTrie(int freq[]) {
    std::priority_queue<TrieNode*, std::vector<TrieNode*>, CompareFrequency> Q;
    
    for(int c=0; c<R; c++){
        if(freq[c] > 0){
            Q.push(new TrieNode((char)c, freq[c], NULL, NULL));
        }
    }
    
    while(Q.size() > 1) {
        TrieNode *right = Q.top();
        Q.pop();
        TrieNode *left = Q.top();
        Q.pop();
        
        Q.push(new TrieNode('\0', right->freq+left->freq, left, right));
    }
    TrieNode* root_tmp = Q.top();
       
    this->root = root_tmp;
}


string Huffman::buildCode(TrieNode *root){
    string s;
    s.resize(R);
    buildCode(&s, root, "");
    return s;
}

void Huffman::buildCode(string st[], TrieNode *x, string s){
    if(x->isLeaf()) {
        st[x->c] = s;
        return;
    }
    buildCode(st, x->left, s + '0');
    buildCode(st, x->right, s + '1');
}
    