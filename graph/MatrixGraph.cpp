#include <exception>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Graph.h"

using std::cerr;
using std::endl;

MatrixGraph::MatrixGraph(std::string location) {

    std::ifstream loader;
    loader.open(location.c_str(), std::ios::in);
    int i=0, j=0, s=0;
    loader >> this->_size;
    
    this->matrix = new int*[this->_size];
    
    for(int i=0; i<this->_size; i++){
        this->matrix[i] = new int[this->_size];
        for(int j=0; j<this->_size; j++)
            this->matrix[i][j] = NONE;
    }
    
    while(loader >> s){
        this->matrix[i][j] = s;
        j++;
        if (j==this->_size) {
            i++;
            j=0;
        }
    }
    loader.close();

}

MatrixGraph::MatrixGraph(int size) {
    this->_size = size;
    this->matrix = new int*[size];
    
    for(int i=0; i<this->_size; i++){
        this->matrix[i] = new int[this->_size];
        for(int j=0; j<this->_size; j++)
            this->matrix[i][j] = NONE;
    }
}

MatrixGraph::~MatrixGraph() {
    for(int i=0; i<this->_size; i++){
        delete this->matrix[i];
    }
    delete this->matrix;
}

void MatrixGraph::addEdge(int i, int j, int w) {
    preconditions(i, j, "addEdge");
    this->matrix[i][j] = w;
}

void MatrixGraph::removeEdge(int i, int j) {
    preconditions(i, j, "removeEdge");
    this->matrix[i][j] = NONE;
}

Edge MatrixGraph::getEdge(int i, int j) {
    preconditions(i, j, "getEdge");
    if(this->matrix[i][j] == NONE)
        throw Exception("getEdge: Edge doesnt exist");
    
    Edge edge(i, j, this->matrix[i][j]);
    return edge;
}

bool MatrixGraph::areNeighbors(int i, int j){
    preconditions(i, j, "areNeighbors");
    return this->matrix[i][j] != NONE;
//    return ((this->matrix[i][j] != NONE) || (this->matrix[j][i] != NONE));
}

int MatrixGraph::getWeight(int i, int j){
    preconditions(i, j, "getWeight");
    return this->matrix[i][j];
}

void MatrixGraph::addWeight(int i, int j, int w){
    preconditions(i, j, "addWeight");
    this->matrix[i][j] += w;
}