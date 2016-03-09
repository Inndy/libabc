#include "matrix.hpp"

int main () {
    auto one = new Matrix<int>(3, 3);
    one->one();
    cout << "one: " << one->str() << endl;

    auto two = new Matrix<int>(one);
    two->add(two);
    cout << "two: " << two->str() << endl;

    auto d = two->mul(two);
    cout << d->str() << endl;
    delete d;

    return 0;
}
