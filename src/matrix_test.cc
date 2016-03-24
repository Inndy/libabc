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
    
    auto queueTest = new Queue<int>();
    for (int index = 0; index < 10; index ++) {
        queueTest->enQueue(index);
    }
    for (int index = 0; index < 10; index ++) {
        int temp = (int)queueTest->deQueue();
        cout << "stack test temp: " << temp << endl;
    }
    queueTest->clear();
    cout << "Cleaned successful? " << queueTest->isEmpty();
    for (int index = 15; index < 20; index ++) {
        queueTest->enQueue(index);
    }
    while (!queueTest->isEmpty()) {
        int temp = (int)queueTest->deQueue();
        cout << "an other test: " << temp << endl;
    }
    delete queueTest;
    
    RPN reverter;
    reverter.command = "123.454,222,333.5+++23";
    reverter.test();
    
    return 0;
}
