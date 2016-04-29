#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"

int main () {
    myVecD * vector0 = new myVecD(3);
    for (int index = 0; index < 3; index++) {
        (*vector0)[index] = 1;
    }
    cout << vector0->str() << endl;
    
    
    LoadFile * lf = new LoadFile("V1.txt");
    int v_count;

    myVecD ** vectors = lf->load_vector(v_count);

    for (int index = 0; index < v_count; index++) {
        cout << vectors[index]->str() << endl;

    }

    
    
    
    
//    Matrix<double> * mat = new Matrix<double>(3,2);
//    for (int indexa = 0; indexa < 3; indexa++) {
//        for (int indexb = 0; indexb < 2; indexb++) {
//            mat->cell(indexa, indexb) = 1;
//        }
//    }
//    cout << mat->str() << endl;
//    delete mat;
    
    return 0;
}
