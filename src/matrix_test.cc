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
    cout << "dot test " << c->dot(*c,*d) << endl;
    cout << "re-directioned dot test " << c->dot(c,d) << endl;
    cout << "cross product " << c->crossProduct(c,d)->str() << endl;
    cout << "triangle area test " << c->triangleAreaWith(d);
    cout << "appro " << approximately_equals(1.0,1.00001) << endl;
    cout << "orthogonal judge " << c->orth_judge(d) << endl;
    delete d;
    delete c;
    return 0;
}
