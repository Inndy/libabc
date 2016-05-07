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
const int AS_COLUMN = 0;
const int AS_ROW = 1;
const double THRESHOLD = 0.0000001;
struct TK{
    int data_type;
    double scalar;
    std::string function_name;
    std::string variable_name;
    char op;
};

double absolute_value(double x){
    if (x < 0) {
        return -x;
    }
    return x;
}

//retrun true is the difference betweeen a and b is lower than THRESHOLD
bool approximately_equals(double a, double b){
    if(absolute_value(a-b) < THRESHOLD)
        return true;
    else return false;
}


#endif