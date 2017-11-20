#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <iostream>
#include <string>

#define NONE 0


using std::string;
using std::cerr;
using std::exception;
using std::endl;

struct Exception : public exception {
   string s;
   Exception(string ss) : s(ss) {}
   ~Exception() throw () {}
   const char* what() const throw() { return s.c_str(); }
};

class ListGraph;
class BellmanFordAlgorithm;

class Edge {
    friend class ListGraph;
    public:
        Edge(int from, int to, int weight) {
            this->_from = from;
            this->_to = to;
            this->weight = weight;
            next = NULL;
        }
        virtual ~Edge() {}
        
        int getFrom() { return _from; }
        int getTo() { return _to; }
        int getWeight() { return weight; }
        Edge* getNext() { return next; }

    private:
        int _from;
        int _to;
        int weight;
        Edge* next;
};

class AbstractGraph {
    public:
        AbstractGraph() {};
        virtual ~AbstractGraph() {};
        
        virtual void addEdge(int i, int j, int weight) = NONE;
        virtual void removeEdge(int i, int j) = NONE;
        virtual Edge getEdge(int i, int j) = NONE;
        
        virtual bool areNeighbors(int i, int j) = NONE;
        virtual int getWeight(int i, int j) = NONE;
        virtual void addWeight(int i, int j, int weight) = NONE;
        
        void pExc(exception &e) {cerr << "Exception: " << e.what() << endl;}
        int size(){return this->_size;}
        void preconditions(int i, int j, string fun){
            if (i >= this->size() || j >= this->size())
                throw Exception(fun + ": i or j > size");
        }
        
    protected:
        int _size;
};


class MatrixGraph : public AbstractGraph {
    public:
        MatrixGraph(string location);
        MatrixGraph(int size);
        ~MatrixGraph();
        
        void addEdge(int i, int j, int weight);
        void removeEdge(int i, int j);
        Edge getEdge(int i, int j);
        
        bool areNeighbors(int i, int j);
        int getWeight(int i, int j);
        void addWeight(int i, int j, int weight);
    
    private:
        int **matrix;
};

class ListGraph : public AbstractGraph {
    friend class BellmanFordAlgorithm;
    public:
        ListGraph(string location);
        ListGraph(int size);
        ~ListGraph();
        
        void addEdge(int i, int j, int weight);
        void removeEdge(int i, int j);
        Edge getEdge(int i, int j);
        
        bool areNeighbors(int i, int j);
        int getWeight(int i, int j);
        void addWeight(int i, int j, int weight);
        
        ListGraph* clone();
        
    private:
        Edge** edges;
};

#endif /* GRAPH_H */

