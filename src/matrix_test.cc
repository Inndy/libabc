#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"

int main () {
    
    
    
    myVecD * c = new myVecD(3);
    (*c)[0] = -3;
    (*c)[1] = -1;
    (*c)[2] = 4;
    myVecD * d = new myVecD(3);
    (*d)[0] = 2;
    (*d)[1] = 14;
    (*d)[2] = 5;

    Matrix<double> * mat;
    Vector<double> ** vectors = new Vector<double>*[2];
    vectors[0] = c; vectors[1] = d;
    mat = mat->merge_by_vectors(AS_COLUMN,2,vectors);
    cout << mat->str() << endl;
    delete d;
    delete c;
    return 0;
}
