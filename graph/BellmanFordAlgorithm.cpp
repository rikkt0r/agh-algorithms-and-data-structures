#include <stdexcept>

#include "Algorithm.h"

using std::cerr;

BellmanFordAlgorithm::BellmanFordAlgorithm() {}
BellmanFordAlgorithm::~BellmanFordAlgorithm() {}

void BellmanFordAlgorithm::run(MatrixGraph& graph, int source){
    int size = graph.size();
    bool changed;
    int *d = new int[size];
    int *pi = new int[size];

    for(int i = 0; i < size; i++) {
        d[i] = INF;
        pi[i] = -1;
    }

    d[source] = 0;

    for(int i = 1; i < size; i++) {
        changed = false;
        for(int from = 0; from < size; from++) {
            for(int to = 0; to < size; to++) {
                if(graph.areNeighbors(from, to) && d[from] + graph.getWeight(from, to) < d[to]) {
                    d[to] = d[from] + graph.getWeight(from, to);
                    pi[to] = from;
                    changed = true;
                }
            }
        }
        if(!changed)
            break;
    }
    
    // v.d <= u.d + w(u, v); ===> not  ===> v.d > u.d + w(u, v)
    for(int from = 0; from < size; from++) {
        for(int to = 0; to < size; to++) {
            if(graph.areNeighbors(from, to) && d[from] + graph.getWeight(from,to) < d[to]) {
                throw Exception("Negative-weight cycle");
            }
        }
    }
    
    
    cerr << "Source: " << source << endl;
    int node = 0;
    
    for(int i=0; i<graph.size(); i++){
        
        cerr << "Node: " << (char)(64+i) << endl << "Predecessors: ";
        node = i;
        while(node != source){
            cerr << (char)(64+node) << ", ";
            node = pi[node];
        }
        cerr << endl << "Weight: " << d[i] << endl;
        cerr << endl;
    }


    delete[] pi;
    delete[] d;
}

void BellmanFordAlgorithm::run(ListGraph& graph, int source){
    int size = graph.size();
    int *d = new int[size];
    int *pi = new int[size];
    bool changed;

    for(int i = 0; i < size; i++) {
        d[i] = INF;
        pi[i] = -1;
    }

    d[source] = 0;
    
    Edge* tmp = NULL;
    for(int i = 1; i < size; i++) {
        changed = false;
        for(int j = 0; j < size; j++) {
            tmp = graph.edges[j];
            while(tmp != NULL) {
                int from = tmp->getFrom();
                int to = tmp ->getTo();
                int w = tmp->getWeight();
                if(d[from] + w < d[to]) {
                    d[to] = d[from] + w;
                    pi[to] = from;
                    changed = true;
                }
                tmp = tmp->getNext();
            }
        }
        if(!changed)
            break;
    }

    // v.d <= u.d + w(u, v);
    for(int from = 0; from < size; from++) {
        tmp = graph.edges[from];
        while(tmp != NULL) {
            if(d[tmp->getFrom()] + tmp->getWeight() < d[tmp->getTo()]) {
                throw Exception("Negative-weight cycle");
            }
            tmp = tmp->getNext();
        }
    }

    cerr << "Source: " << source << endl;
    int node = 0;
    
    for(int i=0; i<graph.size(); i++){
        
        cerr << "Node: " << (char)(64+i) << endl << "Predecessors: ";
        node = i;
        while(node != source) {
            cerr << (char)(64+node) << ", ";
            node = pi[node];
        }
        cerr << endl << "Weight: " << d[i] << endl;
        cerr << endl;
    }

    delete[] pi;
    delete[] d;
}
