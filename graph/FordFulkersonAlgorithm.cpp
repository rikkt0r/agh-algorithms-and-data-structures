#include "Algorithm.h"

using namespace std;

bool FordFulkersonAlgorithm::bfs(MatrixGraph* graph, int start, int sink, int* parent, int* flow) {
    int size = graph->size();
    bool *visited = new bool[size];
    memset(visited, 0, size*sizeof(bool));
    queue <int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < size; v++)
        {
            if (visited[v] == false && graph->getWeight(u,v) - flow[u+size*v] >0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    int result = visited[sink] == true;
    delete[] visited;
    return result;
}

bool FordFulkersonAlgorithm::bfs(ListGraph* graph, int start, int sink, int* parent, ListGraph* flow) {
    int size = graph->size();
    bool *visited = new bool[size];
    memset(visited, 0, size*sizeof(bool));
    queue <int> q;
    q.push(start);
    visited[start] = true;
    parent[start] = -1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < size; v++)
        {
            if (visited[v] == false && (graph->getWeight(u,v) - flow->getWeight(u, v)) >0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    int result = visited[sink] == true;
    delete[] visited;
    return result;
}

int FordFulkersonAlgorithm::run(MatrixGraph* graph, int start, int sink) {
    int size = graph->size();
    int* rGraph = new int[size*size];

    int* parent = new int[size];
    memset(rGraph, 0, size*size*sizeof(int));

    int maxFlow = 0;
    
    while (bfs(graph, start, sink, parent, rGraph)) {
       
       int pathFlow = INT32_MAX;
       for (int u = sink; u != start; u = parent[u]) {
           int currCost = graph->getWeight(parent[u], u);
           int a = rGraph[parent[u] + size*u];
           pathFlow = MIN(pathFlow, currCost - a);
       }
       
       for (int u = sink; u != start; u = parent[u]) {
           rGraph[parent[u] + size*u] += pathFlow; // rGraph[parent[u]][u]
           rGraph[u + size*parent[u]] -= pathFlow; // rGraph[u][parent[u]]
       }
       maxFlow += pathFlow;
    }

    delete[] rGraph;
    delete[] parent;

    return maxFlow;
}




int FordFulkersonAlgorithm::run(ListGraph* graph, int start, int sink) {
    int size = graph->size();
    ListGraph* rGraph = graph->clone();

    int* parent = new int[size];

    int maxFlow = 0;
    while (bfs(graph, start, sink, parent, rGraph)) {
       int pathFlow = INT32_MAX;
       for (int u = sink; u != start; u = parent[u]) {
           pathFlow = MIN(pathFlow, graph->getWeight(parent[u], u) - rGraph->getWeight(parent[u], u));
       }
       for (int u = sink; u != start; u = parent[u]) {
           rGraph->addWeight(parent[u], u, pathFlow);
           rGraph->addWeight(u, parent[u], -pathFlow);
       }
       maxFlow += pathFlow;
    }

    delete rGraph;
    delete[] parent;

    return maxFlow;
}
