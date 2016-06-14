#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"
#include "polynomial.hpp"

int main () {

    myVecD ** vecs = new myVecD*[4];
    for(int index = 0; index < 5; index++){
        vecs[index] = new myVecD(2);
    }
    (*vecs[0])[0] = -1.3; (*vecs[0])[1] = 0.103;
    (*vecs[1])[0] = -0.1; (*vecs[1])[1] = 1.099;
    (*vecs[2])[0] = 0.2; (*vecs[2])[1] = 0.808;
    (*vecs[3])[0] = 1.3; (*vecs[3])[1] = 1.897;
       // (*vecs[5])[0] = 5; (*vecs[5])[1] = 5;
    double a,b;
    myMatD::linear_least_square_method(a,b,vecs,4);
    std::cout << a <<"," << b;
    return 0;
}
