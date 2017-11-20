#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <exception>
#include "Queue.h"
#include "Graph.h"

#include <cstdint>
#include <limits>
#include <cstring>
#include <climits>
#include <queue>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define INF 9999999

class BellmanFordAlgorithm {
    public:
        BellmanFordAlgorithm();
        virtual ~BellmanFordAlgorithm();
        
        static void run(MatrixGraph& graph, int source);
        static void run(ListGraph& graph, int source);
};

class FordFulkersonAlgorithm {
    public:
        FordFulkersonAlgorithm(AbstractGraph& graph);
        virtual ~FordFulkersonAlgorithm();
        
        static bool bfs(MatrixGraph* graph, int start, int sink, int* parent, int* flow);
        static bool bfs(ListGraph* graph, int start, int sink, int* parent, ListGraph* flow);
        static int run(MatrixGraph* graph, int start, int sink);
        static int run(ListGraph* graph, int start, int sink);
};

#endif /* ALGORITHM_H */

