#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"
#include "polynomial.hpp"

int main () {
    Polynomial p(3);
    p[0] = 1;
    p[1] = 2;
    p[2] = 1;
    for (double index = -3.0; index <1; index += 0.1) {
        cout << " " << p(index) << " ";
    }
    cout << endl;
    int count;
    double * result = p.root_finding(count);
    cout << "We find " << count << " roots for the current polynomial, whose values are" << endl;
    for (int index = 0; index < count; index++) {
        cout << " " << result[index] << " ";
    }
    cout << endl;
    return 0;
}
