#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"

int main () {
//    myVecD * vector0 = new myVecD(3);
//    for (int index = 0; index < 3; index++) {
//        (*vector0)[index] = 1;
//    }
//    cout << vector0->str() << endl;
//    
//    
//    LoadFile * lf = new LoadFile("V1.txt");
//    int v_count;
//
//    myVecD ** vectors = lf->load_vector(v_count);
//
//    for (int index = 0; index < v_count; index++) {
//        cout << vectors[index]->str() << endl;
//
//    }
    
    Matrix<double> * mat = new Matrix<double>(3,3);
    /*  7  2  1
     *  0  3 -1
     * -3  4 -2
     */
    mat->cell(0,0) = 2; mat->cell(0,1) = 1; mat->cell(0,2) = -1;
    mat->cell(1,0) = -3; mat->cell(1,1) = -1; mat->cell(1,2) = 2;
    mat->cell(2,0) = -2;mat->cell(2,1) = 1; mat->cell(2,2) = 2;
    myVecD vec(3);
    mat->gaussian_elimination(*mat);
    cout << mat->str() << endl;
    
    Matrix<double> * mat1 = new Matrix<double>(3,3);
    /*  7  2  1
     *  0  3 -1
     * -3  4 -2
     */
    mat1->cell(0,0) = 7; mat1->cell(0,1) = 2; mat1->cell(0,2) = 1;
    mat1->cell(1,0) = 0; mat1->cell(1,1) = 3; mat1->cell(1,2) = -1;
    mat1->cell(2,0) = -3;mat1->cell(2,1) = 4; mat1->cell(2,2) = -2;
    
//    cout << mat->mul(mat1).str() << endl;
    
    
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
