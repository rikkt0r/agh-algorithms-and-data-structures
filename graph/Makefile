CXX=g++
DEBUG=-g
CXXFLAGS=-std=c++11 -Wall -c $(DEBUG)
LFLAGS=-std=c++11 -Wall $(DEBUG)

OBJS=BellmanFordAlgorithm.o FordFulkersonAlgorithm.o

all: graphs

graphs: $(OBJS) main.cpp
	$(CXX) $(LFLAGS) main.cpp $(OBJS) -o graphs

BellmanFordAlgorithm.o: Algorithm.h ListGraph.o MatrixGraph.o Queue.o BellmanFordAlgorithm.cpp
	$(CXX) $(CXXFLAGS) Queue.o ListGraph.o MatrixGraph.o BellmanFordAlgorithm.cpp

FordFulkersonAlgorithm.o: Algorithm.h ListGraph.o MatrixGraph.o Queue.o FordFulkersonAlgorithm.cpp
	$(CXX) $(CXXFLAGS) Queue.o ListGraph.o MatrixGraph.o FordFulkersonAlgorithm.cpp

Queue.o: Queue.h Queue.cpp
	$(CXX) $(CXXFLAGS) Queue.cpp

ListGraph.o: Graph.h ListGraph.cpp
	$(CXX) $(CXXFLAGS) ListGraph.cpp

MatrixGraph.o: Graph.h MatrixGraph.cpp
	$(CXX) $(CXXFLAGS) MatrixGraph.cpp

clean:
	rm graphs *.o *.gch
