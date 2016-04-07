/* utilities
 */
#ifndef util_hpp
#define util_hpp
#define fatal(mesg) { std::cerr << mesg << std::endl; exit(1); }
#define myVecD Vector<double>
template<class T>
class Node{
public:
    Node * previous;
    Node * next;
    T data;
};

const int SCALAR_TYPE = 0;
const int FUNCTION_TYPE = 1;
const int VARIABLE_TYPE = 2;
const int OPERATOR_TYPE = 3;
struct TK{
    int data_type;
    double scalar;
    std::string function_name;
    std::string variable_name;
    char op;
};

#endif