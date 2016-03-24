#include "stack.hpp"
#include "queue.hpp"
#include "util.hpp"
#include <vector>

/* RPN stands for reverse polish notation, also called Postfix
 * receive a string as a expression
 * first tokenize the string and store it in a queue
 * then turn it into postfix and return a queue
 * 
 * to tokenize the functions and variables form the string input
 * function_name_list and variable_name_list should be set
 */
#define vector std::vector
const char * NUMERIC_CHAR = "0123456789.";
const char * OPERATOR_CHAR = "+-*/!^()";
const int SCALAR_TYPE = 0;
const int FUNCTION_TYPE = 1;
const int VARIABLE_TYPE = 2;
const int OPERATOR_TYPE = 3;


class RPN{
public:
    RPN(){}

    vector<std::string> function_name_list;
    vector<std::string> variable_name_list;
    std::string command;
    
    void test(){
        tokenize();
        while (!tokenizedEquation.isEmpty()) {
            std::cout << tokenizedEquation.deQueue().scalar << " , ";
        }
        cout << endl;
    }
private:
    Queue<TK> tokenizedEquation;
    void tokenize(){
        vector<char> temp;
        std::cout << "Enter Tokenized" << std::endl;
        for(int index = 0; index < command.size(); index++){
            std::cout << "hello, world" << std::endl;
            //if the current char is numeric char
            if (isNumericChar(command[index])) {
                //get all the numeric chars
                while (index < command.size() && isNumericChar(command[index])) {
                    temp.push_back(command[index]);
                    index ++;
                }
                TK currentTK;
                currentTK.data_type = SCALAR_TYPE;
                char * convertedstr = convert(temp);
                currentTK.scalar = atof(convertedstr);
                tokenizedEquation.enQueue(currentTK);
                delete convertedstr;
                temp.clear();
            }
        }
    }
    
    bool isNumericChar(char ch){
        for (int index = 0; index < strlen(NUMERIC_CHAR); index++) {
            if (ch == NUMERIC_CHAR[index]) {
                return true;
            }
        }
        return false;
    }
    
    bool isOperatorChar(char ch){
        for(int index = 0; index < strlen(OPERATOR_CHAR); index++){
            if(ch == OPERATOR_CHAR[index])
                return true;
        }
        return false;
    }
    
    char *convert(const vector<char> & v)
    {
        char *pc = new char[v.size()+1];
        for (int index = 0; index < v.size(); index++) {
            pc[index] = v[index];
        }
        pc[v.size()] = '\0';
        return pc;
    }
    
};