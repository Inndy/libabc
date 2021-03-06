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
//        cout << "size " <<size << endl;
        this->size = size;
        this->allocate_buffer();
    }
    ~Vector(){
        this->free_buffer();
    }
    
    void init_to_zero(){
        for (int index = 0; index < this->size; index++) {
            (*this)[index] = 0;
        }
    }
    //vector-addition
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
    //scalar-multiplication
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
    //vector-dot
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
    //vector-norm
    double norm(){
        double result = 0.0;
        for (int index = 0; index < this->size; index++) {
            result += this->data[index] * this->data[index];
        }
        return sqrt(result);
    }
    
    //normalize the vector. set it's magnitude to 1 while maintaining it's other property
    //vector-normalization
    Vector * normalize(){
        double norm = this->norm();
        for (int index = 0; index < this->size; index++) {
            this->data[index] /= norm;
        }
        return this;
    }
    
    //cross product of a and b, only in 3 dimension
    //vector-cross-product
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
    //vector-component
    double componentOn(Vector * b){
        if(!VEC_SIZE_MATCH_THIS_P(b))
            fatal("vector size unmatch");
        return Vector::dot(*this,*b)/b->norm();
    }

    //projection of this on b
    //vector-projection
    Vector * projectionOn(Vector * b){
        if(!VEC_SIZE_MATCH_THIS_P(b))
            fatal("vector size unmatch");
        Vector * tempb = b->copy();
        tempb->normalize();
        return tempb->mul(this->componentOn(b));
    }

    //triangle area of this and b, only avaliable for 3-dimensional problem
    //vector-triangle-area
    double triangleAreaWith(Vector * b){
        return triangleArea(this,b);
    }
    //triangle area, only avaliable for 3-dimensional problem
    static double triangleArea(Vector * a, Vector * b){
        double result = Vector::crossProduct(a,b)->norm();
        return result/2;
    }

    //vector-angle-between
    //static version of angle between vector a and b
    //return the radian of the angle between the two vectors
    static double angleBetween(Vector * a, Vector * b){
        return acos(dot(a,b)/a->norm()/b->norm());
    }
    double angleBetween(Vector * b){
        return angleBetween(this,b);
    }

    //judge if the two input vector is parallel
    //vector-parallel-judgement
    static bool para_judge(Vector * a, Vector * b){
        return approximately_equals(0.0,angleBetween(a,b))||approximately_equals(3.141592653589,angleBetween(a,b));
    }
    //judge if this vector and the input vector is parallel
    bool para_judge(Vector * b){
        return para_judge(this, b);
    }

    //vector-orthogonal-judgement
    //judge if the two input vector is orthogonal
    static bool orth_judge(Vector * a, Vector * b){
        return approximately_equals(0.0, dot(a,b));
    }
    //judge if this vector and the input vector is orthogonal
    bool orth_judge(Vector * b){
        return orth_judge(this, b);
    }

    //vector-plane-normal
    //return the normal vector of the plane produced by two vectors
    //only for 3-dimensional problem
    static Vector * normal_vector_of_plane2v(Vector * a, Vector * b){
        return crossProduct(a,b)->normalize();
    }
    //orthogonal projection this on b
    // (this•b)/(b•b)  *  b
    //
    Vector * orth_proj(Vector * b){
        double temp = dot(this,b)/dot(b,b);
        return b->mul(temp);
    }

    //vector-orthogonal-basis
    static void find_orthogonal_basis_of_basis(Vector ** basis, int base_count){
        Gram_Schidt(basis,base_count);
    }
    //Gram_Schidt orthogonalization process
    static void Gram_Schidt(Vector ** vectors, int vec_count){
        //check if the input is valid
        //check if the size of the input set is valid
        if (vec_count == 0) {
            fatal("Gram_Schidt: null basis set input");
        }
        //check if all the input vectors has the same size
        auto dimension = vectors[0]->size;
        for (int index = 0; index < vec_count; index++) {
            if(vectors[index]->size != dimension)
                fatal("Gram_Schidt: input basis set error");
        }
        //declear result array
        Vector ** result = new Vector*[vec_count];

        for (int index = 0; index < vec_count; index++) {
            result[index] = vectors[index];
            for (int indexa = index-1; indexa>=0; indexa--) {
                myVecD * temp = new myVecD(dimension);
                for (int indexb = 0; indexb < dimension; indexb++) {
                    (*temp)[indexb] = (*result[indexa])[indexb];
                }
                result[index]->sub( temp->mul((dot(vectors[index],result[indexa])/dot(result[indexa],result[indexa])))    );
                delete temp;
            }
        }
        //normalize
        for (int index = 0; index < vec_count; index++) {
            result[index]->normalize();
        }
        vectors = result;

    }
private:

};

#endif