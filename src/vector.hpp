#ifndef vector_hpp
#define vector_hpp
#include "util.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdint.h>

using namespace std;

template<class T>
class Vector{
private:
    T *data;
    void allocate_buffer(){
        if(size <= 0)
            fatal("size can't be zero");
        this->data = new T[size];
    }
    void free_buffer(){
        delete [] data;
    }
public:
    int size;
    Vector(int size){
        this->size = size;
        cout << "size" << size << endl;
        this->allocate_buffer();
    }
    ~Vector(){
        this->free_buffer();
    }
    
    //accessor to element
    T& operator[] (int index){
        if(index >= this->size)
            fatal("Element index larger than Vector size");
        return data[index];
    }
    
    //dot operation between double vector
    static double dot(Vector<double> & a, Vector<double> & b){
        if(!a.getSize() == b.getSize())
            fatal("vector size unmatching");
        double result = 0.0;
        for (int index = 0; index < a.getSize(); index++) {
            result += a[index]*b[index];
        }
        
        return result;
    }
//    the following function is malfunctioning
//    static double dot(Vector<double> * a, Vector<double> * b){
//        a->dot(*a,*b);
//    }
    
    int getSize(){
        return this->size;
    }
    
    string str(){
        stringstream buffer;
        buffer << "Vector(" << this->size << ")\n{ ";
        for (int index = 0; index < this->size; index ++) {
            if (index) {
                buffer << ", ";
            }
            buffer << (*this)[index];
        }
        buffer << " } ";
        return buffer.str();
    }
private:
    
};

#endif