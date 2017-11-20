CXX=g++
DEBUG=-g
CXXFLAGS=-std=c++11 -Wall -c -fopenmp -pthread $(DEBUG)
LFLAGS=-std=c++11 -Wall -fopenmp -pthread $(DEBUG)


all: sort

sort:
	$(CXX) $(LFLAGS) main.cpp -o sort

clean:
	rm sort *.o *.gch
