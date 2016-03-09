#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdint.h>

#define fatal(mesg) { std::cerr << mesg << std::endl; exit(1); }
#define MATRIX_FOREACH(I, J) \
            for(auto I = 0; I < this->h; I++) \
                for(auto J = 0; J < this->h; J++)
#define MATRIX_SIZE_MATCH(M) \
            ((M)->w != this->w || (M)->h != this->h)
#define MATRIX_SIZE_SHOULD_BE_SAME(M) \
            if(MATRIX_SIZE_MATCH((M))) \
                fatal("matrix size mismatch");

using namespace std;

template<class T>
class Matrix
{
    private:
        T **data;

        void allocate_buffer() {
            if(h == 0 || w == 0)
                fatal("neither `h` or `w` can be zero");
            this->data = new T*[h];
            for(auto i = 0; i < this->h; i++)
                this->data[i] = new T[w];
        }

        void free_buffer() {
            for(auto i = 0; i < this->h; i++)
                delete [] this->data[i];
            delete [] this->data;
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
            return this->data[x][y];
        }

        T& cell(int x, int y) {
            return this->data[x][y];
        }



        // data manipulation
        Matrix* copy_from(Matrix *m) {
            MATRIX_SIZE_SHOULD_BE_SAME(m);
            MATRIX_FOREACH(x, y) {
                this->data[x][y] = m->cell(x, y);
            }
            return this;
        }

        Matrix* add(Matrix *m) {
            MATRIX_SIZE_SHOULD_BE_SAME(m);
            MATRIX_FOREACH(x, y) {
                this->data[x][y] += m->cell(x, y);
            }
            return this;
        }
        Matrix* add(Matrix& m) {
            return this->add(&m);
        }

        Matrix* sub(Matrix *m) {
            MATRIX_SIZE_SHOULD_BE_SAME(m);
            MATRIX_FOREACH(x, y) {
                this->data[x][y] -= m->cell(x, y);
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
                        sum += this->data[x][j] * m->cell(j, y);
                    result->cell(x, y) = sum;
                }
            }
            return result;
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



        void fill(T value) {
            MATRIX_FOREACH(x, y) {
                this->data[x][y] = value;
            }
        }

        void zero() {
            MATRIX_FOREACH(x, y) {
                this->data[x][y] = 0;
            }
        }

        void one() {
            MATRIX_FOREACH(x, y) {
                this->data[x][y] = x == y ? 1 : 0;
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
                    buffer << this->data[x][y];
                }
                buffer << ")";
            }
            buffer << "\n}";

            return buffer.str();
        }
};
