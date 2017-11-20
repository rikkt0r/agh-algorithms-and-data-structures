#ifndef QUEUE_H
#define QUEUE_H

struct node{
    int data;
    struct node *next;
};

class Queue{
    private:
        node *qback;
        node *qfront;
        node *qcurrent;
        int qsize;

    public:
        Queue();
        Queue(const Queue &queue);
        ~Queue();
        
        void push(int val);
        int pop();
        bool empty();
        int size();
        
        int front();
        int back();
        int current();
        
        bool next();
        void reset();
        void display();
};

#endif /* QUEUE_H */

