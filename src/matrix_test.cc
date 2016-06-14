#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"
#include "util.hpp"
#include "vector.hpp"
#include "polynomial.hpp"

int main () {
    myVecD * vector1 = new myVecD(2);
    (*vector1)[0] = 1;
    (*vector1)[1] = 0;

    myVecD * vector2 = new myVecD(2);
    (*vector2)[0] = 0;
    (*vector2)[1] = 1;

    std::cout << "angle " << vector1->angleBetween(vector1,vector2) << std::endl;
    std::cout << "parallel judge" << vector1->orth_judge(vector2) << std::endl;

    return 0;
}
