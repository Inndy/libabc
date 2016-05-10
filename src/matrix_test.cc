#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"
#include "polynomial.hpp"

int main () {
    myMatD * mat = new myMatD(3,3);
    mat->cell(0,0) = 1; mat->cell(0,1) = 3; mat->cell(0,2) = 0;
    mat->cell(1,0) = 2; mat->cell(1,1) = 6; mat->cell(1,2) = 4;
    mat->cell(2,0) = -1; mat->cell(2,1) = 0; mat->cell(2,2) = 2;

    cout << mat->str();
    cout << mat->cofactorMatrix(2,2)->str();
    cout << mat->det(mat->cofactorMatrix(2,2)) << endl;
    cout << mat->det(mat);

    return 0;
}
