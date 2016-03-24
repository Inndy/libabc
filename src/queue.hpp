#ifndef queue_hpp
#define queue_hpp

#include "util.hpp"
/* FIFO
 */
template<class T>
class Queue{
public:
    Queue(){
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

    }
    bool isEmpty(){
        return start == nullptr;
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
private:
    Node<T> * start;
    Node<T> * end;
};
#endif