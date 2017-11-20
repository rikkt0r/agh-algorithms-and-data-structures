CXX=g++
DEBUG=-g
CXXFLAGS=-std=c++11 -Wall -c -fopenmp -pthread $(DEBUG)
LFLAGS=-std=c++11 -Wall -fopenmp -pthread $(DEBUG)

OBJS=BinaryFileHandler.o Huffman.o TrieNode.o


all: huffman

huffman: $(OBJS)
	$(CXX) $(LFLAGS) main.cpp $(OBJS) -o huffman

Huffman.o: BinaryFileHandler.o TrieNode.o Huffman.cpp Huffman.h
	$(CXX) $(CXXFLAGS) Huffman.cpp Huffman.h

BinaryFileHandler.o: BinaryFileHandler.cpp BinaryFileHandler.h
	$(CXX) $(CXXFLAGS) BinaryFileHandler.cpp BinaryFileHandler.h

TrieNode.o: TrieNode.cpp TrieNode.h
	$(CXX) $(CXXFLAGS) TrieNode.cpp TrieNode.h

clean:
	rm huffman *.o *.gch
