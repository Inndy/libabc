#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"

int main () {
    
    myVecD a = myVecD(3);
    (a)[0] = 1;
    (a)[1] = 3;
    (a)[2] = -5;
    myVecD b = myVecD(3);
    (b)[0] = 4;
    (b)[1] = -2;
    (b)[2] = -1;
    
    cout << "hello world" << endl;
    cout << a.str() << endl;
    cout << b.str() << endl;
    cout << b[0] <<endl;
    cout << b[1] << endl;
    cout << "dot" << a.dot(a,b) << endl;
    
    
    return 0;
}
