#ifndef BINARYFILEHANDLER_H
#define BINARYFILEHANDLER_H

#include <cerrno>
#include <string>
#include <bitset>
#include <iostream>
#include <fstream>

using std::string;

class BinaryFileHandler {
public:
    BinaryFileHandler(string fileName, bool write);
    virtual ~BinaryFileHandler();
    
    string readAll();
    
    bool readBool();
    char readChar();
    int  readInt();
    
    void writeBin(bool b);
    void writeBin(int i);
    void writeBin(char c);
    
    void write(char c);
    void write(string s);
    
    
private:
    std::fstream file;
};

#endif /* BINARYFILEHANDLER_H */

