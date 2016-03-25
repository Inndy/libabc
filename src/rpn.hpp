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
const char * OPERATOR_CHAR = "+-*/!^(),";
const char * NAME_CHAR = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_$0123456789";
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
            TK current = tokenizedEquation.deQueue();
            switch (current.data_type) {
                case SCALAR_TYPE:
                    std::cout << current.scalar << " , ";
                    break;
                case OPERATOR_TYPE:
                    std::cout << current.op << " , ";
                    break;
                case VARIABLE_TYPE:
                    std::cout << current.variable_name << " , ";
                    break;
                case FUNCTION_TYPE:
                    std::cout << current.function_name << " , ";
                    break;
                default:
                    break;
            }
            //std::cout << temp << " , ";
        }
        cout << endl;
    }
private:
    Queue<TK> tokenizedEquation;
    void tokenize(){
        vector<char> temp;
        std::cout << "Enter Tokenized" << std::endl;
        for(int index = 0; index < command.size(); index++){
            //if the current char is numeric char
            if (isNumericChar(command[index])) {
                //get all the numeric chars
                temp.clear();
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
                index --;
            }
            //if the current char is operator
            else if(isOperatorChar(command[index])){
                TK currentTK;
                currentTK.data_type = OPERATOR_TYPE;
                if (command[index] == ',') {
                    currentTK.op = ')';
                    tokenizedEquation.enQueue(currentTK);
                    currentTK.op = '(';
                    tokenizedEquation.enQueue(currentTK);
                }else{
                    currentTK.op = command[index];
                    tokenizedEquation.enQueue(currentTK);
                }
            }
            //rule of variable/function name: can not start with numeric char or operator
            //if the current char is neither an operator nor a number
            //it must be a start of a variable name or function name
            //end with operator type char(for variable "+-*/^!"; for function '(' )
            else if(isNameChar(command[index])){
                temp.clear();
                while (index < command.size() && isNameChar(command[index])) {
                    temp.push_back(command[index]);
                    index ++;
                }
                if (isVariableName(convert(temp))) {
                    TK currentTK;
                    currentTK.data_type = VARIABLE_TYPE;
                    currentTK.variable_name = convert(temp);
                    tokenizedEquation.enQueue(currentTK);
                }else if(isFunctionName(convert(temp))&&command[index] == '('){
                    TK currentTK;
                    currentTK.data_type = FUNCTION_TYPE;
                    currentTK.function_name = convert(temp);
                    tokenizedEquation.enQueue(currentTK);
                }else{
                    std::string error_message;
                    error_message = "Undefined expression ";
                    error_message += convert(temp);
                    fatal(error_message);
                }
                index--;
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
    
    bool isNameChar(char ch){
        for (int index = 0; index < strlen(NAME_CHAR); index++) {
            if(ch == NAME_CHAR[index])
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
    

    
    bool isVariableName(const char * s){
        for (vector<string>::iterator iter = variable_name_list.begin();
             iter != variable_name_list.end();
             iter ++) {
            if(strcmp(*iter, s))
                return true;
        }
        return false;
    }
    
    bool isFunctionName(const char * s){
        for (vector<string>::iterator iter = function_name_list.begin();
             iter != function_name_list.end();
             iter ++) {
            if(strcmp(*iter, s))
                return true;
        }
        return false;
    }
    
    bool strcmp(std::string s1, const char * s2){
        if (s1.size() != strlen(s2)) {
            return false;
        }
        for (int index = 0; index < s1.size(); index++) {
            if (s1[index]!= s2[index]) {
                return false;
            }
        }
        return true;
    }
};