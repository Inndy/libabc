#ifndef vector_hpp
#define vector_hpp
#include "util.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <math.h>

#define VEC_SIZE_MATCH_THIS_P(V) \
    (this->size == V->size)
#define VEC_SIZE_EQUAL_R(U,V) \
    (U.size == V.size)

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
    
    Vector * add(Vector * v){
        if (!VEC_SIZE_MATCH_THIS_P(v)) {
            fatal("vector size unmatch")
        }
        for (int index = 0; index < this->size; index++) {
            data[index] += (*v)[index];
        }
        return this;
    }
    
    Vector * add(Vector & v){
        return this->add(&v);
    }
    
    Vector * sub(Vector * v){
        if(!VEC_SIZE_MATCH_THIS_P(v))
            fatal("vector size unmatch");
        for (int index = 0; index < this->size; index++) {
            data[index] -= (*v)[index];
        }
        return this;
    }
    
    Vector * sub(Vector & v){
        return this->sub(&v);
    }
    
    Vector * mul(T scalar){
        for (int index = 0; index < this->size; index++) {
            this->data[index] *= scalar;
        }
        return this;
    }
    
    Vector * div(T scalar){
        for (int index = 0; index < this->size; index++) {
            this->data[index] /= scalar;
        }
        return this;
    }
    
    //accessor to element
    T& operator[] (int index){
        if(index >= this->size)
            fatal("Element index larger than Vector size");
        return data[index];
    }
    
    //dot operation between double vector
    static double dot(Vector<double> & a, Vector<double> & b){
        if(!VEC_SIZE_EQUAL_R(a,b))
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
    
    //norm, or we say magnitute of vector
    double norm(){
        double result = 0.0;
        for (int index = 0; index < this->size; index++) {
            result += this->data[index] * this->data[index];
        }
        return sqrt(result);
    }
private:
    
};

#endif