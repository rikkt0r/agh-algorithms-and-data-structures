#include <chrono>

#include "Huffman.h"

using namespace std;
using namespace std::chrono;

void turnOffScientificNotation(){
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(8);
}

int main() {
    
    high_resolution_clock::time_point start, finish;
    duration<double> dtime;
    
    turnOffScientificNotation();
    
    // #######################################################################
    start = high_resolution_clock::now();
    cout << "Huffman sequential -------------------------" << endl;
    
    Huffman h = Huffman();
    h.encode("input.txt", "code_trie.bin.txt", "encoded.bin.txt");
    h.decode("encoded.bin.txt", "code_trie.bin.txt", "output.txt");
    
    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);
    cout << endl << "Time elapsed: " << dtime.count() << endl << endl;
    
    // #######################################################################
    start = high_resolution_clock::now();
    cout << endl << "Huffman parallel ----------------------------" << endl;
    
    Huffman h_p = Huffman();
    h_p.encodeParallel("input.txt", "code_trie_parallel.bin.txt", "encoded_parallel.bin.txt");
    h_p.decodeParallel("encoded_parallel.bin.txt", "code_trie_parallel.bin.txt", "output_parallel.txt");
    
    finish = high_resolution_clock::now();
    dtime = duration_cast<duration<double>>(finish-start);
    cout << "Time elapsed: " << dtime.count() << endl << endl;
    
    // #######################################################################
    


    return 0;
}
