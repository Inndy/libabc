#ifndef queue_hpp
#define queue_hpp

#include "util.hpp"
/* FIFO
 */
template<class T>
class Queue{
public:
    Queue(){
        size = 0;
        start = nullptr;
        end = nullptr;
    }
    
    ~Queue(){
        clear();
    }

    void clear(){
        while (!isEmpty()) {
            Node<T> * tempStart = start;
            start = start->next;
            delete tempStart;
            start->previous = nullptr;
        }
        size = 0;
    }
    
    bool isEmpty(){
        return start == nullptr;
    }
    
    int getSize(){
        return this->size;
    }
    
    void enQueue(T data){
        if(isEmpty()){
            start = new Node<T>();
            start->data = data;
            end = start;
        }
        else{
            end->next = new Node<T>();
            Node<T> * tempEnd = end;
            end = end->next;
            end->data = data;
            end->previous = tempEnd;
        }
        size ++;
    }
    
    T deQueue(){
        T temp = start->data;
        if(end != start){
            Node<T> * tempStart = start->next;
            delete start;
            start = tempStart;
            start->previous = nullptr;
        }
        else{
            end = nullptr;
            start = nullptr;
        }
        return temp;
    }
    
    T & operator [] (int index){
        if(index >= size)
            fatal("Element index larger than queue length");
        Node<T> * current;
        current = start;
        for (int count = 0; count < index ; count ++) {
            current = current->next;
        }
        return current->data;
    }
    
    private:
    Node<T> * start;
    Node<T> * end;
    int size;
};
#endif