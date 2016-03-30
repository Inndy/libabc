#ifndef stack_hpp
#define stack_hpp
#include "util.hpp"
/* FILO
 */
#include <iostream>
using namespace std;
template <class T>
class Stack{
public:
    Stack(){
        start = nullptr;
        end = nullptr;
    }
    ~Stack(){
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
    void push(T data){
        if (isEmpty()) {
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
    T pop(){
        if(isEmpty())
            fatal("Pop() form empty stack");
        T temp = end->data;
        if(end != start)
        {
            Node<T> * tempEnd = end->previous;
            delete end;
            end = tempEnd;
            end->next = nullptr;
        }
        else{
            end = nullptr;
            start = nullptr;
        }
        return temp;
    }
    T peek(){
        if (isEmpty()) {
            fatal("Peek() form empty stack");
        }
        T temp = end->data;
        return temp;
    }
private:
    Node<T> * start;
    Node<T> * end;
};
#endif