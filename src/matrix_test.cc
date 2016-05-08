#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"
#include "polynomial.hpp"

int main () {
    myMatD * mat = new myMatD(2,2);
    mat->cell(0,0) = -5; mat->cell(0,1) =  2;// mat->cell(0,2) = -3;
    mat->cell(1,0) =  2; mat->cell(1,1) =  -2;// mat->cell(1,2) = -6;
//    mat->cell(2,0) = -1; mat->cell(2,1) = -2; mat->cell(2,2) =  0;
    vector<double> eigen_values;
    vector<myVecD>eigen_vectors;
    mat->eigen_value_vector(eigen_values,eigen_vectors);

    return 0;
}
