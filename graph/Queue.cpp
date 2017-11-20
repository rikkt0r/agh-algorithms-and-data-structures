#include <iostream>
#include <cstdlib>
#include <queue>
#include "Queue.h"

using namespace std;

Queue::Queue(){
    qback = NULL;
    qfront = NULL;
    qcurrent = NULL;
    qsize = 0;
}

Queue::Queue(const Queue& queue){
    
}

Queue::~Queue(){
    
}

// -----------------------------------------------------------------------------

void Queue::push(int val){
    node *temp = new node;
    temp->data = val;
    temp->next = NULL;

    if(this->qfront == NULL){
        this->qfront = temp;
    } else{
        this->qback->next = temp;
    }
    this->qback = temp;
    
    this->qsize++;
}

int Queue::pop(){
    node *temp = new node;
    int data;

    if(this->qfront == NULL){
        cout << "Queue is Empty" << endl;
    } else{
        temp = this->qfront;
        this->qfront = this->qfront->next;
        data = temp->data;
        delete temp;
        this->qsize--;
        return data;
    }
}

bool Queue::empty() {
    if(this->qfront == NULL)
        return true;
    else
        return false;
}

int Queue::size(){
    return this->qsize;
}

// -----------------------------------------------------------------------------
int Queue::front() {
    if(!this->empty()){
        return this->qback->data;
    } else {
        cout << "Queue is Empty" << endl;
        return 0;
    }
}

int Queue::back() {
    if(!this->empty()){
        return this->qfront->data;
    } else {
        cout << "Queue is Empty" << endl;
        return 0;
    }
}

int Queue::current() {
    if(this->empty())
        cout << "Queue is Empty" << endl;
    return this->qcurrent->data;
}

bool Queue::next(){
    if(this->qcurrent->next != NULL) {
        this->qcurrent = this->qcurrent->next;
        return true;
    } else
        return false;
}

void Queue::reset(){
    node *tmp = new node;
    tmp->next = this->qfront;
    this->qcurrent = tmp;
}
// -----------------------------------------------------------------------------

void Queue::display(){

    this->reset();
    while(this->next()){
        cout << this->current() << ", ";
    }
    cout << endl;
}
