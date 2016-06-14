#ifndef queue_hpp
#define queue_hpp

#include "util.hpp"
#include <deque>

/* FIFO */
template<class T>
class Queue{
public:
    Queue() {
    }

    ~Queue(){
        clear();
    }

    void clear(){
        Q.clear();
    }

    bool isEmpty(){
        return Q.empty();
    }

    int getSize(){
        return Q.size();
    }

    void enQueue(T data){
        Q.push_back(data);
    }

    T deQueue(){
        T obj = Q.front();
        Q.pop_front();
        return obj;
    }

    T & operator [] (int index){
        if(index >= Q.size())
            fatal("Element index larger than queue length");
        return Q[index];
    }

    private:
        std::deque<T> Q;
};

#endif
