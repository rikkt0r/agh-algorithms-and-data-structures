#include <cstdlib>
#include <iostream>
#include "Graph.h"
#include "Algorithm.h"

using namespace std;

int main() {
    
    //MatrixGraph mg = MatrixGraph("/home/rikkt0r/cpp-agh/graph/graph.txt");
    
    cerr << " ---------- BellmanFord Matrix -----------" << endl;
    MatrixGraph mg = MatrixGraph(6);
    mg.addEdge(0, 1, 1);
    mg.addEdge(0, 2, 8);
    mg.addEdge(1, 3, 6);
    mg.addEdge(2, 3, 3);
    mg.addEdge(2, 4, 2);
    mg.addEdge(2, 5, -4);
    mg.addEdge(3, 5, 2);
    mg.addEdge(5, 4, -5);
    BellmanFordAlgorithm::run(mg, 0);
    
    cerr << " ---------- BellmanFord List -----------" << endl;
    ListGraph lg = ListGraph(6);
    lg.addEdge(0, 1, 1);
    lg.addEdge(0, 2, 8);
    lg.addEdge(1, 3, 6);
    lg.addEdge(2, 3, 3);
    lg.addEdge(2, 4, 2);
    lg.addEdge(2, 5, -4);
    lg.addEdge(3, 5, 2);
    lg.addEdge(5, 4, -5);
    BellmanFordAlgorithm::run(lg, 0);
    
    cerr << " ---------- BellmanFord Matrix 2 -----------" << endl;
    MatrixGraph mg2 = MatrixGraph(8);
    mg2.addEdge(0, 1, 3);
    mg2.addEdge(0, 2, 1);
    mg2.addEdge(0, 5, 5);
    mg2.addEdge(1, 4, 6);
    mg2.addEdge(2, 6, 2);
    mg2.addEdge(2, 7, -1);
    mg2.addEdge(4, 3, 1);
    mg2.addEdge(5, 1, 5);
    mg2.addEdge(5, 7, 3);
    mg2.addEdge(6, 7, 4);
    mg2.addEdge(7, 4, 2);
    BellmanFordAlgorithm::run(mg2, 0);

    
    cerr << " ---------- FordFulkerson Matrix -----------" << endl;
    MatrixGraph mg3 = MatrixGraph(5);
    mg3.addEdge(0, 1, 12);
    mg3.addEdge(0, 2, 10);
    mg3.addEdge(1, 2, 9);
    mg3.addEdge(1, 3, 4);
    mg3.addEdge(2, 3, 5);
    mg3.addEdge(2, 4, 8);
    mg3.addEdge(3, 4, 20);
    cerr << "Max flow: " << FordFulkersonAlgorithm::run(&mg3, 0, 4) << endl;
    
    cerr << " ---------- FordFulkerson List -----------" << endl;
    ListGraph lg2 = ListGraph(5);
    lg2.addEdge(0, 1, 12);
    lg2.addEdge(0, 2, 10);
    lg2.addEdge(1, 2, 9);
    lg2.addEdge(1, 3, 4);
    lg2.addEdge(2, 3, 5);
    lg2.addEdge(2, 4, 8);
    lg2.addEdge(3, 4, 20);
    
    cerr << "Max flow: " << FordFulkersonAlgorithm::run(&lg2, 0, 4) << endl;

    
    return 0;
}