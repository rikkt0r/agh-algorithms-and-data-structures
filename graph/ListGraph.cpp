#include <exception>
#include <iostream>
#include <fstream>
#include "Graph.h"

ListGraph::ListGraph(std::string location) {
    std::ifstream loader;
    loader.open(location.c_str(), std::ios::in);
    int i=0, j=0, s=0;
    loader >> this->_size;
    
    edges = new Edge*[this->size()];
    for(int i = 0; i < this->size(); i++) {
        edges[i] = NULL;
    }
    
    while(loader >> s){

    }
    loader.close();
}

ListGraph::ListGraph(int size) {
    this->_size = size;
    edges = new Edge*[size];
    for(int i = 0; i < size; i++) {
        edges[i] = NULL;
    }
}

ListGraph::~ListGraph() {
    Edge* toDelete;
    Edge* tmp;
    for(int i = 0; i < this->size(); i++) {
        if(edges[i]) {
            tmp = edges[i];
            while(tmp && tmp->next != NULL) {
                toDelete = tmp;
                tmp = tmp->next;
                delete toDelete;
            }
            delete tmp;
        }
    }
    delete[] edges;
}


//TODO
void ListGraph::removeEdge(int i, int j) {
    preconditions(i, j, "removeEdge");
//    try {
//        this->matrix[i][j] = 0;
//        this->matrix[j][i] = 0;
//    } catch(std::exception &e) {
//        pExc(e);
//    }
}

void ListGraph::addEdge(int i, int j, int w) {
    preconditions(i, j, "addEdge");
    Edge* edge = new Edge(i, j, w);

    if(edges[i] == NULL) {
        edges[i] = edge;
    } else {
        if(!areNeighbors(i, j)) {
            edge->next = edges[i];
            edges[i] = edge;
        }
    }
}

// TODO
Edge ListGraph::getEdge(int i, int j) {
    preconditions(i, j, "getEdge");
    Edge edge = Edge(i, j, 5);
    return edge;
}

bool ListGraph::areNeighbors(int i, int j){
    preconditions(i, j, "areNeighbors");
    Edge* list = edges[i];
    while(list != NULL) {
        if(list->_to == j) {
            return true;
        } else {
            list = list->next;
        }
    }
    return false;
}

int ListGraph::getWeight(int i, int j){
    preconditions(i, j, "getWeight");
    Edge* list = edges[i];

    while(list != NULL) {
        if(list->_to == j) {
            return list->weight;
        }
        list = list->next;
    }
    return NONE;
}

void ListGraph::addWeight(int i, int j, int w){
    preconditions(i, j, "addWeight");
    Edge* list = edges[i];

    while(list != NULL) {
        if(list->_to == j) {
            list->weight += w;
            return;
        }
    }
}

ListGraph* ListGraph::clone() {
    ListGraph* tmp = new ListGraph(this->size());
    for(int i = 0; i < this->size(); i++) {
        Edge* e = edges[i];
        while(e != NULL) {
            tmp->addEdge(i, e->_to, e->weight);
            e = e->next;
        }
    }
    return tmp;
}