#include "matrix.hpp"
#include "loadfile.hpp"
#include "queue.hpp"
#include "rpn.hpp"

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
    
 
    
    RPN reverter;
    reverter.variable_name_list.push_back("var");
    reverter.function_name_list.push_back("var1");
    reverter.command = "var1(1+2,2)*(3+4)";
    reverter.test();
    
    return 0;
}
