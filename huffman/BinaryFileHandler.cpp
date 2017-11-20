#include "BinaryFileHandler.h"

using std::string;
using std::cerr;
using std::endl;

BinaryFileHandler::BinaryFileHandler(string fileName, bool write) {
    if(write)
        this->file.open(fileName.c_str(), std::ios::out | std::ios::trunc);
    else
        this->file.open(fileName.c_str(), std::ios::in);
    
    if(this->file.fail())
        cerr << "Unable to open file for read/write;" << endl;
}

BinaryFileHandler::~BinaryFileHandler() {
    this->file.flush();
    this->file.close();
}

string BinaryFileHandler::readAll() {
    string contents;
    file.seekg(0, std::ios::end);
    contents.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&contents[0], contents.size());

    return(contents);
}

bool BinaryFileHandler::readBool(){
    string s;
    s.resize(1);
    file.read(&s[0], 1);
    return s != "0";
}
char BinaryFileHandler::readChar(){
    char s[8];
    file.read(s, 8);
    std::bitset<8> b(s);
    return (char)b.to_ulong();
}
int  BinaryFileHandler::readInt(){
    char s[32];
    file.read(s, 32);
    std::bitset<32> b(s);
    return (int)b.to_ulong();
}

void BinaryFileHandler::writeBin(bool b){
    file << (int)b;
    file.flush();
}

void BinaryFileHandler::writeBin(int i){
    file << std::bitset<32>(i);
    file.flush();
}

void BinaryFileHandler::writeBin(char c){
    file << std::bitset<8>(c);
    file.flush();
}

void BinaryFileHandler::write(string s){
    file << s;
    file.flush();
}

void BinaryFileHandler::write(char c){
    file << c;
    file.flush();
}

