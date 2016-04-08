#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include "util.hpp"
#include "vector.hpp"


#define debug(X) X

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
            debug({ fprintf(stderr, "[+] Matrix allocaed at %p, Buffer allocated at %p\n", this, this->data); })
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



        // data accessor
        T& operator() (int x, int y) {
            return this->data[x * this->h + y];
        }

        T& cell(int x, int y) {
            return this->data[x * this->h + y];
        }



        // data manipulation
        Matrix* copy_from(Matrix *m) {
            MATRIX_SIZE_SHOULD_BE_SAME(m);
            memcpy(&this->cell(0, 0), &m->cell(0, 0), sizeof(T) * this->w * this->h);
            return this;
        }

        Matrix* add(Matrix *m) {
            MATRIX_SIZE_SHOULD_BE_SAME(m);
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) += m->cell(x, y);
            }
            return this;
        }
        Matrix* add(Matrix& m) {
            return this->add(&m);
        }

        Matrix* sub(Matrix *m) {
            MATRIX_SIZE_SHOULD_BE_SAME(m);
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) -= m->cell(x, y);
            }
            return this;
        }
        Matrix* sub(Matrix& m) {
            return this->sub(&m);
        }

        Matrix* mul(Matrix *m) {
            if(this->w != m->h)
                fatal("matrix size mismatch (mul)");

            // result height, result width
            auto r_h = this->h, r_w = m->w, len = this->w;
            Matrix *result = new Matrix(r_h, r_w);
            for(auto x = 0; x < r_h; x++) {
                for(auto y = 0; y < r_w; y++) {
                    T sum = 0;
                    for(auto j = 0; j < len; j++)
                        sum += this->cell(x, j) * m->cell(j, y);
                    result->cell(x, y) = sum;
                }
            }
            return result;
        }
        Matrix* mul(T v) {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) *= v;
            }
            return this;
        }

        Matrix* div(T v) {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) /= v;
            }
            return this;
        }



        // operator overloading, all size check is perfrom in named functions
        Matrix* operator= (const Matrix& m) {
            return this->copy_from(&m);
        }

        Matrix* operator+= (Matrix& m) { return this->add(m); }
        Matrix* operator+= (Matrix *m) { return this->add(m); }

        Matrix* operator-= (Matrix& m) { return this->sub(m); }
        Matrix* operator-= (Matrix *m) { return this->sub(m); }



        // these operator will return new Matrix instance
        Matrix* operator+ (Matrix& m) {
            Matrix *result = new Matrix(this);
            result->add(m);
            return result;
        }



        Matrix* fill(T value) {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) = value;
            }
            return this;
        }

        Matrix* zero() {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) = 0;
            }
            return this;
        }

        Matrix* one() {
            MATRIX_FOREACH(x, y) {
                this->cell(x, y) = x == y ? 1 : 0;
            }
            return this;
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
        myVecD * mul(myVecD * v){
            if(!MATRIX_WIDTH_VECTOR_SIZE_MATCH_P(v))
                fatal("matrix's width != vector's length");
            myVecD * result = new myVecD(this->h);
            for (int index = 0; index < this->h; index++) {
                (*result)[index] = 0.0;
            }
            for (int index = 0; index < this->h; index++) {
                for (int indexa = 0; indexa < this->w; indexa ++) {
                    (*result)[index] += (this->data[indexa][index] * ((*v)[indexa]));
                }
            }
            return result;
        }
        myVecD * mul(myVecD & v){
            return this->mul(&v);
        }
        // static method
        static Matrix* one(int h, int w) {
           return (new Matrix(h, w))->one();
        }
};
