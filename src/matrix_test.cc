#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"

int main () {
    
    
    
    myVecD * c = new myVecD(3);
    (*c)[0] = 1;
    (*c)[2] = 2;
    (*c)[1] = 3;
    Matrix<double> * mat = new Matrix<double>(3,3);
    for (int index = 0; index < 3; index++) {
        for (int indexa = 0; indexa < 3; indexa++) {
            mat->cell(index,indexa) = 1.0;
        }
    }
    myVecD * d = mat->mul(c);
    cout << d->str() <<endl;
    cout << "vector norm test " << c->norm() << endl;
    delete c;
    return 0;
}
