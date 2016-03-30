#ifndef rpn_hpp
#define rpn_hpp

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

const int priority[8][8] = {
    //        +   -   *   /   ^   !   (   ,
    {/* + */  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
    {/* - */  0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
    {/* * */  1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
    {/* / */  1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 },
    {/* ^ */  1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 },
    {/* ! */  1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 },
    {/* ( */  1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 },
    {/* , */  1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 }
};
const int ADD_OP = 0;
const int MINUS_OP = 1;
const int MUL_OP = 2;
const int DIV_OP = 3;
const int POW_OP = 4;
const int FACTORIAL_OP = 5;
const int BRACKET_OP = 6;
const int DOT_OP = 7;


class RPN{
public:
    RPN(){}

    vector<std::string> function_name_list;
    vector<std::string> variable_name_list;
    std::string command;
    
    void test(){
        decode();
        std::cout << "hello,11world" << std::endl;
        while (!result.isEmpty()) {
            TK current = result.deQueue();
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
        std::cout << endl;
        std::cout << "hello,world22" << std::endl;
    }
    
    void decode(){
        tokenize();
        checkError();
        reverse();
    }
    Queue<TK> result;
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
//                if (command[index] == ',') {
//                    currentTK.op = ')';
//                    tokenizedEquation.enQueue(currentTK);
//                    currentTK.op = '(';
//                    tokenizedEquation.enQueue(currentTK);
//                }
//                else{
                    currentTK.op = command[index];
                    tokenizedEquation.enQueue(currentTK);
//                }
            }
            //rule of variable/function name: can not start with numeric char or operator
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
    
    void checkError(){
        checkBrackets();
        //TO-DO
    }
    
    void reverse(){
        result.clear();
        Stack<TK> op_memory;
        while (!tokenizedEquation.isEmpty()) {
            TK temp = tokenizedEquation.deQueue();
            switch (temp.data_type) {
                case SCALAR_TYPE:
                    result.enQueue(temp);
                    break;
                case VARIABLE_TYPE:
                    result.enQueue(temp);
                    break;
                case FUNCTION_TYPE:
                    op_memory.push(temp);
                    break;
                case OPERATOR_TYPE:
                    if (temp.op == '(') {
                        std::cout << "case (" << std::endl;
                        op_memory.push(temp);
                    
                    }else if (temp.op != ',' && temp.op != ')') {
                        std::cout << "+-*/ enter, with data " << temp.op << std::endl;
                        
                        if (op_memory.isEmpty()) {
                            std::cout << "case empty" << std::endl;
                            op_memory.push(temp);
                        }else if(priorTo(temp, op_memory.peek())){
                            std::cout << "case prior to peek" << std::endl;
                            op_memory.push(temp);
                        }else{
                            std::cout << "case non-prior to peek" << std::endl;
                            while (!priorTo(temp, op_memory.peek()) && op_memory.peek().op != '(') {
                                result.enQueue(op_memory.pop());
                                if (op_memory.isEmpty()) {
                                    break;
                                }
                            }
                            op_memory.push(temp);
                        }
                        
                        
                    }else if(temp.op == ','){
                        TK tempa = op_memory.pop();
                        while (tempa.data_type != OPERATOR_TYPE && tempa.op !='(') {
                            result.enQueue(tempa);
                        }
                        op_memory.push(tempa);
                    }else if(temp.op == ')'){
                        std::cout << ") type dected" << std::endl;
//                        while (!op_memory.isEmpty()) {
//                            std::cout << op_memory.pop().op << std::endl;
//                        }
                        while (op_memory.peek().op != '(' ) {
                            auto tempa = op_memory.pop();
                            std::cout << tempa.op << std::endl;
                            result.enQueue(tempa);
                        }
                        op_memory.pop();
                        if (!op_memory.isEmpty() && op_memory.peek().data_type == FUNCTION_TYPE) {
                            result.enQueue(op_memory.pop());
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        while (!op_memory.isEmpty()) {
            result.enQueue(op_memory.pop());
        }
    }
    
    void checkBrackets(){
        int br_count = 0;
        for (int index = 0; index < tokenizedEquation.getSize(); index++) {

            if (tokenizedEquation[index].data_type == OPERATOR_TYPE && tokenizedEquation[index].op == '(') {
                br_count ++;
            }
            else if(tokenizedEquation[index].data_type == OPERATOR_TYPE && tokenizedEquation[index].op == ')'){
                br_count --;
            }
            if (br_count < 0) {
                fatal("Illegal equation: brackets unpaired");
            }
        }
        if (br_count != 0) {
            fatal("Illegal equation: braktets unpaired");
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
    //e.g. key1 is add, key 2 is *, return 0
    bool priorTo(TK key1, TK key2){
        int _1key, _2key;
        _1key = trans(key1.op);
        _2key = trans(key2.op);
        return priority[_1key][_2key];
        
    }
    
    int trans(char op){
        switch (op) {
            case '+':
                return ADD_OP;
            case '-':
                return MINUS_OP;
            case '*':
                return MUL_OP;
            case '/':
                return DIV_OP;
            case '^':
                return POW_OP;
            case '!':
                return FACTORIAL_OP;
            case '(':
                return BRACKET_OP;
            case ',':
                return DOT_OP;

                
            default:
                break;
        }
    }
};

#endif