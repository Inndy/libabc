#include "matrix.hpp"

int main () {
    Matrix<int> a(5, 5);
    a.one();
    a(3, 4) = 8;
    a.Hi();

    Matrix<int> b = a;
    b.Hi();

    Matrix<int> c(b.h, b.w);
    c.copy_from(a);
    c.Hi();
}
