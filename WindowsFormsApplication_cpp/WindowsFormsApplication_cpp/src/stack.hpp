#ifndef stack_hpp
#define stack_hpp

#include "util.hpp"
#include <stack>

/* FILO */
template <class T>
class Stack{
public:
    Stack() { }
    ~Stack() { }

    bool isEmpty(){
        return S.empty();
    }

    void push(T data){
        S.push(data);
    }

    T pop(){
        T obj = S.top();
        S.pop();
        return obj;
    }

    T peek(){
        if (isEmpty()) {
            fatal("Peek() form empty stack");
        }
        return S.top();
    }
private:
    std::stack<T> S;
};
#endif
