CXX=g++
DEBUG=-g
CXXFLAGS=-std=c++11 -Wall -c -fopenmp -pthread $(DEBUG)
LFLAGS=-std=c++11 -Wall -fopenmp -pthread $(DEBUG)

OBJS=pi.o

all: pi

pi: $(OBJS)
	$(CXX) $(LFLAGS) main.cpp $(OBJS) -o pi

pi.o: pi.cpp pi.h
	$(CXX) $(CXXFLAGS) pi.cpp

clean:
	rm *.o pi *.gch
