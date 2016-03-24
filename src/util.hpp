/* utilities
 */
#ifndef util_hpp
#define util_hpp
template<class T>
class Node{
public:
    Node * previous;
    Node * next;
    T data;
};

struct TK{
    int data_type;
    double scalar;
    std::string function_name;
    std::string variable_name;
    char op;
};

#endif 