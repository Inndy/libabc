#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"
#include "polynomial.hpp"

int main () {
    myMatD * mat = new myMatD(3,3);
    mat->cell(0,0) = 0; mat->cell(0,1) = 0; mat->cell(0,2) = 0;
    mat->cell(1,0) = -3; mat->cell(1,1) = 0; mat->cell(1,2) = 1;
    mat->cell(2,0) = 3;mat->cell(2,1) = 0; mat->cell(2,2) = -1;
    std::cout << mat->rank() << std::endl;
    return 0;
}
