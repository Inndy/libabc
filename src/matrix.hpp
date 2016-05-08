#ifndef matrix_hpp
#define matrix_hpp

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <vector>
#include "util.hpp"
#include "vector.hpp"
#include "polynomial.hpp"


#ifndef debug
#define debug(X) X
#endif

#define MATRIX_FOREACH(I, J) \
            for(auto I = 0; I < this->h; I++) \
                for(auto J = 0; J < this->h; J++)
#define MATRIX_SIZE_MATCH(M) \
            ((M)->w != this->w || (M)->h != this->h)
#define MATRIX_SIZE_SHOULD_BE_SAME(M) \
            if(MATRIX_SIZE_MATCH((M))) \
                fatal("matrix size mismatch");
#define MATRIX_WIDTH_VECTOR_SIZE_MATCH_P(V) \
            (this->w == V->size)
using namespace std;

template<class T>
class Matrix
{
    private:
        T *data;

        void allocate_buffer() {
            if(this->h == 0 || this->w == 0)
                fatal("neither `h` or `w` can be zero");

            this->data = new T[this->h * this->w];
            //debug({ fprintf(stderr, "[+] Matrix allocaed at %p, Buffer allocated at %p\n", this, this->data); })
        }

        void free_buffer() {
            if(this->data == NULL)
                fatal("buffer is NULL, can not be freed");
            debug({ fprintf(stderr, "[+] Buffer freed %p\n", this->data); })

            delete [] (char *)this->data;
            this->data = NULL;
        }

    public:
        const uint32_t h, w;

        // constructor and destructor
        Matrix(uint32_t h, uint32_t w) : h(h), w(w)
        {
            this->allocate_buffer();
            this->zero();
        }

        Matrix(Matrix& m) : h(m.h), w(m.w)
        {
            this->allocate_buffer();
            this->copy_from(&m);
        }

        Matrix(Matrix *m) : h(m->h), w(m->w)
        {
            this->allocate_buffer();
            this->copy_from(m);
        }

        ~Matrix() {
            this->free_buffer();
        }

        void copy_from(Matrix *m) {
            MATRIX_SIZE_SHOULD_BE_SAME(m);
            memcpy(&this->cell(0, 0), &m->cell(0, 0), sizeof(T) * this->w * this->h);
        }



        // data accessor
        T& operator() (int x, int y) {
            return this->data[x * this->h + y];
        }

        T& cell(int x, int y) {
            return this->data[x * this->h + y];
        }



        // data manipulation
        Matrix& add(Matrix &m) {
            MATRIX_SIZE_SHOULD_BE_SAME(&m);
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) += m(x, y);
            }
            return *this;
        }

        Matrix& sub(Matrix &m) {
            MATRIX_SIZE_SHOULD_BE_SAME(&m);
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) -= m(x, y);
            }
            return &this;
        }

        Matrix& mul(Matrix *m) {
            cout << this->str();
            cout << m->str();
            if(this->w != m->h)
                fatal("matrix size mismatch (mul)");

            // result height, result width
            auto r_h = this->h, r_w = m->w, len = this->w;
            Matrix<T> * result = new Matrix<T>(r_h, r_w);
            for(auto x = 0; x < r_h; x++) {
                for(auto y = 0; y < r_w; y++) {
                    T sum = 0;
                    for(auto j = 0; j < len; j++)
                        sum += this->cell(x, j) * m->cell(j, y);
                    (*result)(x, y) = sum;
                }
            }
            return (*result);
        }
    
    
        Matrix& mul(T v) {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) *= v;
            }
            return *this;
        }

        Matrix& div(T v) {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) /= v;
            }
            return *this;
        }



        // operator overloading, all size check is perfrom in named functions
        Matrix& operator= (const Matrix& m) {
            return *this->copy_from(&m);
        }

        Matrix& operator+= (Matrix& m) { return *this->add(m); }
        Matrix& operator+= (Matrix *m) { return *this->add(m); }

        Matrix& operator-= (Matrix& m) { return *this->sub(m); }
        Matrix& operator-= (Matrix *m) { return *this->sub(m); }



        // these operator will return new Matrix instance
        Matrix& operator+ (Matrix& m) {
            Matrix result(this);
            return result.add(m);
        }



        void fill(T value) {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) = value;
            }
        }

        void zero() {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) = 0;
            }
        }

        void one() {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) = x == y ? 1 : 0;
            }
        }



        string str() {
            stringstream buffer;
            buffer << "Matrix(" << h << ", " << w << ") {\n";
            for(auto x = 0; x < this->h; x++) {
                if(x) buffer << ",\n";
                buffer << "  (";
                for(auto y = 0; y < this->w; y++) {
                    if(y) buffer << ", ";
                    buffer << this->cell(x, y);
                }
                buffer << ")";
            }
            buffer << "\n}";

            return buffer.str();
        }
        //matrix multiply vector
        myVecD& mul(myVecD * v){
            if(!MATRIX_WIDTH_VECTOR_SIZE_MATCH_P(v))
                fatal("matrix's width != vector's length");
            myVecD * result = new myVecD(this->h);
            for (int index = 0; index < this->h; index++) {
                (*result)[index] = 0.0;
            }
            for (int index = 0; index < this->h; index++) {
                for (int indexa = 0; indexa < this->w; indexa ++) {
                    (*result)[index] += (this->cell(index,indexa) * (*v)[indexa]);
                }
            }
            return (*result);
        }
        myVecD * mul(myVecD & v){
            return this->mul(&v);
        }
        //trace of a matrix
        //only avaliable for square matrix
        double trace(){
            if(this->h != this->w)
                fatal("Matrix: trace method: non-square matrix intput");
            double result = 0;
            for (int index = 0; index < this->h; index++) {
                result += this->cell(index,index);
            }
            return result;
        }

        void eigen_value_vector(std::vector<double> & eigen_values,std::vector<myVecD> & eigen_vectors){
            //the eigen value problem is only avaible for square matrices
            if (this->w != this->h) {
                fatal("EigenValue Problem: non-square matrix input");
            }
        //=======================================
            //calculate eigenvalue
            /*-----------------------------*/
            //generate characteristic polynomial
            Polynomial * characteristic_polynomial = generate_characteristic_polynomial();
            cout << characteristic_polynomial->str();

        }
        Polynomial * generate_characteristic_polynomial(){
            Polynomial * result = new Polynomial(h+1);
            (*result)[h] = 1*pow(-1,h);
            myMatD * temp = new myMatD(h,w);
            temp->copy_from(this);
            myMatD * identity = Identity_matrix(this->h);
            for (int index = 1; index <= this->h; index++) {
                if (index > 1) {
                    double factor = (*result)[this->h-index+1];
                    identity->mul(factor);
                    //todo
                    myMatD * tempa = new myMatD(h,w);
                    tempa->copy_from(temp);
                    tempa->add(*identity);
                    myMatD tempb = this->mul(tempa);
                    temp->copy_from(&tempb);
                    delete tempa;
                    identity->div(factor);
                }
                (*result)[this->h - index] = -temp->trace()/(double(index));
            }
            for (int index = 0; index <= this->h-1; index++) {
                (*result)[index] *= pow(-1,h);
            }
            return result;
        }
        //static methods
    //================================
        //method gauss_jordan_elimination receives a matrix A and a vector b\
        it solve x of Ax = b\
        after the elimination the result x of Ax = b will replace vector b\
        the inverse of matrix A will repalce matrix A
        static void gauss_jordan_elimination(Matrix<double> & A, myVecD & b){
            int i,j,k;
            int icol,irow;
            int l,ll,n = A.h, m = 1;
            double big, dum, pivinv;
            std::vector<int> indxc(n),indxr(n), ipiv(n);
            for (j = 0; j < n; j++) ipiv[j] = 0;
            for (i = 0; i < n; i++) {
                big = 0.0;
                for (j = 0; j < n; j++)
                    if (ipiv[j]!=1) {
                        for (k = 0; k < n; k++){
                            if(ipiv[k] == 0){
                                if(absolute_value(A.cell(j,k)) >= big){
                                    big = absolute_value(A.cell(j,k));
                                    irow = j;
                                    icol = k;
                                }//end of if(abs(A.cell(j,k)) >= big)
                            }//end of if(ipiv[k] == 0){
                        }//end of for (k = 0; k < n; k++)
                    }//end of if (ipiv[j]!=1) && end of (j = 0; j < n; j++)
                ++(ipiv[icol]);
                if(irow != icol){
                    for(l = 0; l < n; l++){
                        double _tempa = A.cell(irow,l);
                        A.cell(irow,l) = A.cell(icol,l);
                        A.cell(icol,l) = _tempa;
                    }//end of for(l = 0; l < n; l++)
                    double _tempb = b[irow];
                    b[irow] = b[icol];
                    b[icol] = _tempb;
                }//end of if(irow != icol)
                indxr[i] = irow;
                indxc[i] = icol;
                if(A.cell(icol,icol) == 0.0)
                    fatal("Gauss Jordan Elimination: Sigular Matrix");
                pivinv = 1.0/A.cell(icol,icol);
                A.cell(icol,icol) = 1.0;
                for (l = 0; l < n; l++) A.cell(icol,l) *= pivinv;
                b[icol] *= pivinv;
                for (ll = 0; ll < n; ll ++) {
                    if(ll != icol){
                        dum = A.cell(ll,icol);
                        A.cell(ll,icol) = 0.0;
                        for (l = 0; l < n;l++) A.cell(ll,l) -= A.cell(icol,l)*dum;
                        b[ll] -= b[icol]* dum;
                    }
                }
                
                
                
            }//end of for for (i = 0; i < n; i++)
            for(l = n-1; l >=0; l--){
                if (indxr[l] != indxc[l]) {
                    for (k = 0; k < n; k++) {
                        double _tempa = A.cell(k,indxr[l]);
                        A.cell(k,indxr[l]) = A.cell(k,indxc[l]);
                        A.cell(k,indxc[l]) = _tempa;
                    }
                }
            }
            
        }
    static void gaussian_elimination(Matrix<double> & A){
        int boundary = (A.w<A.h?A.w:A.h);
        for (int index = 0; index < boundary; index++) {
            //pivoting
            double big = 0.0;
            int i_max;
            for (int indexa = index; indexa < A.h; indexa++) {
                if(A.cell(indexa,index)>big){
                    i_max = indexa;
                    big = A.cell(indexa, index);
                }
            }
            //singualr matrix dectect
            if(A.cell(i_max,index) == 0)
                fatal ("Gussian Elimination: Singular Matrix");
            //swap the rows
            if (index != i_max) {
                for (int indexa = 0; indexa < A.w; indexa++) {
                    double _temp = A.cell(index,indexa);
                    A.cell(index,indexa) = A.cell(i_max,indexa);
                    A.cell(i_max,indexa) = _temp;
                }
            }
            //do elimination for all rows below pivot
            for (int indexa = index+1; indexa < A.h; indexa++) {
                //decide the coefficient when minus the piviting row
                double divpiv = A.cell(indexa,index)/A.cell(index,index);
                
                for (int indexb = index+1; indexb< A.w; indexb++) {
                    A.cell(indexa,indexb) = A.cell(indexa,indexb) - A.cell(index,indexb)*divpiv;
                }
                A.cell(indexa,index) = 0;
            }
            
        }
        
    }
    
    static myMatD * Identity_matrix(int n){
        myMatD * result = new myMatD(n,n);
        for (int index = 0; index < n; index++) {
            result->cell(index,index) = 1;
        }
        return result;
    }
    
    
    
    
    
    //TODO
    static Matrix<double> * merge_by_vectors(int merge_type, int number, myVecD ** vectors){
        if(number <= 0)
            fatal("invalid number of vectors");
        int size = vectors[0]->size;
        for (int index = 0; index < number; index++) {
            if(vectors[index]->size != size)
                fatal("vectors with different dimension can't be merged to one matrix");
        }
        Matrix<double> * result;
        int column, row;
        switch(merge_type){
            case AS_COLUMN:
                column = number;
                row  = size;
                result = new Matrix<double>(row, column);
                for (int indexa = 0; indexa < column; indexa++) {
                    for (int indexb = 0; indexb < row; indexb++) {
                        (*result)(indexb, indexa) = 1.0;
                    }
                }
                break;
            case AS_ROW:
                break;
            default:
                fatal("invalid merge type");
        }
        return result;
    }
};

#endif
