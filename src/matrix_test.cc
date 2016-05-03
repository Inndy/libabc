#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"

int main () {
    myVecD ** vectors = new myVecD*[3];
    cout << "hello,world" << endl;
    for (int index = 0; index < 3; index++) {
        vectors[index] = new myVecD(3);
    }


    (*vectors[0])[0] = 1;
    (*vectors[0])[1] = 1;
    (*vectors[0])[2] = 1;

    (*vectors[1])[0] = -0.66666666;
    (*vectors[1])[1] = 0.333333333;
    (*vectors[1])[2] = 0.333333333;

    (*vectors[2])[0] = 0;
    (*vectors[2])[1] = 0.5;
    (*vectors[2])[2] = -0.5;

//    for (int index = 0; index < 3; index++) {
//        cout << vectors[index]->str() << endl;
//    }

    vectors[0]->Gram_Schidt(vectors,3);

    for (int index = 0; index < 3; index++) {
        cout << vectors[index]->str() << endl;
    }
    return 0;
}
