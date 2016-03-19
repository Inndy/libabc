#include "matrix.hpp"
#include "loadfile.hpp"

int main () {
    auto one = Matrix<int>::one(3, 3);
    cout << "one: " << one->str() << endl;

    auto two = Matrix<int>::one(3, 3)->mul(2);
    cout << "two: " << two->str() << endl;

    auto three = (new Matrix<int>(two))->add(one);
    cout << "three: " << three->str() << endl;

    auto four = (new Matrix<int>(two))->mul(2);
    cout << "four: " << four->str() << endl;
    
    delete one;
    delete two;
    delete three;
    delete four;
    Matrix<double> ** matrices;
    LoadFile * lf = new LoadFile("m2.txt");
    cout << lf->getAddress() << endl;
    matrices = lf->load_matrix();
    cout << "load1: " << matrices[5]->str() << endl;
    //lf->test();
    delete lf;
    
    return 0;
}
