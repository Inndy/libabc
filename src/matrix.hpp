#include <iostream>

#define fatal(mesg) { cerr << mesg << endl; exit(1); }
#define MATRIX_FOREACH(I, J) \
            for(auto I = 0; I < this->h; I++) \
                for(auto J = 0; J < this->h; J++)

using namespace std;

template<class T>
class Matrix
{
    private:
        T **data;

        void allocate_buffer() {
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
        const int h, w;

        Matrix(int h, int w) : h(h), w(w)
        {
            this->allocate_buffer();
            this->zero();
        }

        Matrix(const Matrix& m) : h(m.h), w(m.w)
        {
            this->allocate_buffer();
            for(auto i = 0; i < this->h; i++) {
                for(auto j = 0; j < this->w; j++) {
                    // this->data[i][j] = m(i, j);
                }
            }
        }

        ~Matrix() {
            this->free_buffer();
        }



        int& operator() (int x, int y) {
            return this->data[x][y];
        }

        Matrix* copy_from(Matrix& m) {
            if(m.w != this->w || m.h != this->h) {
                fatal("matrix size mismatch");
            }
            MATRIX_FOREACH(x, y) {
                this->data[x][y] = m(x, y);
            }
            return this;
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



        void Hi() {
            std::cout << "Matrix(" << h << ", " << w << ") -> " << this << ", buffer: " << data << endl;
            cout << "(\n";
            for(auto x = 0; x < this->h; x++) {
                if(x) cout << ",\n";
                cout << "  (";
                for(auto y = 0; y < this->w; y++) {
                    if(y) cout << ", ";
                    cout << this->data[x][y];
                }
                cout << ")";
            }
            cout << "\n)" << endl;
        }
};
