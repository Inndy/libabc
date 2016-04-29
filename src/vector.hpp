#ifndef vector_hpp
#define vector_hpp
#include "util.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <math.h>
//#include <tgmath.h>
#include "matrix.hpp"

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
            fatal("vector size unmatch");
        double result = 0.0;
        for (int index = 0; index < a.getSize(); index++) {
            result += a[index]*b[index];
        }
        
        return result;
    }
    //pointer parameter redirection
    static double dot(Vector<double> * a, Vector<double> * b){
        return a->dot(*a,*b);
    }
    
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
    
    Vector * copy(){
        Vector * result = new Vector(size);
        for (int index = 0; index < size; index++) {
            (*result)[index] = (*this)[index];
        }
        return result;
    }
    
    //norm, or we say magnitude of vector
    double norm(){
        double result = 0.0;
        for (int index = 0; index < this->size; index++) {
            result += this->data[index] * this->data[index];
        }
        return sqrt(result);
    }
    
    //normalize the vector. set it's magnitude to 1 while maintaining it's other property
    Vector * normalize(){
        double norm = this->norm();
        for (int index = 0; index < this->size; index++) {
            this->data[index] /= norm;
        }
        return this;
    }
    
    //cross product of a and b, only in 3 dimension
    static Vector * crossProduct(Vector * a, Vector * b){
        if(a->size != 3 || b->size != 3){
            fatal("Cross product only availavle in 3-dimension space");
        }
        Vector * result = new Vector(3);
        (*result)[0] = (*a)[1]*(*b)[2] - (*a)[2]*(*b)[1];
        (*result)[1] = -( (*a)[0]*(*b)[2] - (*a)[2]*(*b)[0] );
        (*result)[2] = (*a)[0]*(*b)[1] - (*a)[1]*(*b)[0];
        return result;
    }
    //component of this on b
    double componentOn(Vector * b){
        if(!VEC_SIZE_MATCH_THIS_P(b))
            fatal("vector size unmatch");
        return Vector::dot(*this,*b)/b->norm();
    }
    //projection of this on b
    Vector * projectionOn(Vector * b){
        if(!VEC_SIZE_MATCH_THIS_P(b))
            fatal("vector size unmatch");
        Vector * tempb = b->copy();
        tempb->normalize();
        return tempb->mul(this->componentOn(b));
    }
    //triangle area of this and b, only avaliable for 3-dimensional problem
    double triangleAreaWith(Vector * b){
        return triangleArea(this,b);
    }
    //triangle area, only avaliable for 3-dimensional problem
    static double triangleArea(Vector * a, Vector * b){
        double result = Vector::crossProduct(a,b)->norm();
        return result/2;
    }
    //static version of angle between vector a and b
    static double angleBetween(Vector * a, Vector * b){
        return acos(dot(a,b)/a->norm()/b->norm());
    }
    double angleBetween(Vector * b){
        return angleBetween(this,b);
    }
    //judge if the two input vector is parallel
    static bool para_judge(Vector * a, Vector * b){
        return approximately_equals(0.0,angleBetween(a,b));
    }
    //judge if this vector and the input vector is parallel
    bool para_judge(Vector * b){
        return para_judge(this, b);
    }
    //judge if the two input vector is orthogonal
    static bool orth_judge(Vector * a, Vector * b){
        return approximately_equals(0.0, dot(a,b));
    }
    //judge if this vector and the input vector is orthogonal
    bool orth_judge(Vector * b){
        return orth_judge(this, b);
    }
    //return the normal vector of the plane produced by two vectors
    //only for 3-dimensional problem
    static Vector * normal_vector_of_plane2v(Vector * a, Vector * b){
        return crossProduct(a,b)->normalize();
    }
private:
    
};

#endif