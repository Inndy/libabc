#ifndef QQ_TOKENS
#define QQ_TOKENS

#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include <iostream>

using namespace std;

// X in [A, B]
#define IN_RANGE(A, X, B) ((A) <= (X) && (X) <= (B))

enum TokenType { T_Token, T_Identity, T_Operator, T_Value, T_Var, T_Pair, T_Assign, T_End, T_Comma };
enum CharType { C_Unknow, C_Number, C_Alphabet, C_Underscore, C_Dot, C_Operator, C_Pair, C_Assign, C_End, C_Comma };

CharType TokenCharType(char ch)
{
    if(IN_RANGE('0', ch, '9')) return C_Number;
    if(IN_RANGE('a', ch, 'z') || IN_RANGE('A', ch, 'Z')) return C_Alphabet;
    switch(ch)
    {
        case '_':
            return C_Underscore;
        case '.':
            return C_Dot;
        case ',':
            return C_Comma;
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
            return C_Operator;
        case '(':
        case ')':
            return C_Pair;
        case '=':
            return C_Assign;
        case ';':
            return C_End;
    }
    return C_Unknow;
}

const char * const TokenTypeToString(TokenType t)
{
    switch(t) {
        default: return "Unknow";
        case T_Assign: return "Assign";
        case T_End: return "End";
        case T_Identity: return "Identity";
        case T_Operator: return "Operator";
        case T_Pair: return "Pair";
        case T_Value: return "Value";
        case T_Var: return "Var";
        case T_Comma: return "Comma";
    }
}

class Token
{
    protected:
        Token(TokenType type) : type_id(type) {  }
    public:
        const TokenType type_id;
        string get_type_str() { return TokenTypeToString(this->type_id); }
        string to_string();
};

class TIdentity : public Token
{
    public:
        const string name;
        TIdentity(string name) : name(name), Token(T_Identity) {  }
        string to_string() { return "<" + this->get_type_str() + "(\"" + this->name + "\")>"; }
};

class TOperator : public Token
{
    public:
        const string op;
        TOperator(string op) : op(op), Token(T_Operator) {  }
        string to_string() { return "<" + this->get_type_str() + "('" + this->op + "')>"; }
};

class TValue : public Token
{
    public:
        const string value;
        double as_double() { return stod(value); }
        TValue(string value) : value(value), Token(T_Value) {  }
        string to_string() { return "<" + this->get_type_str() + "(" + value + ")>"; }
};

class TPair : public Token
{
    public:
        int pos;
        const char type;
        TPair(int pos, char type) : pos(pos), type(type), Token(T_Pair) {  }
        string to_string() { return "<" + this->get_type_str() + "(" + ::to_string(pos) + ", " + string(1, type == '(' ? 'L' : 'R') + ")>"; }
};

class TVar : public Token
{
    public:
        TVar() : Token(T_Var) {  }
};

class TEnd : public Token
{
    public:
        TEnd() : Token(T_End) {  }
};

class TAssign : public Token
{
    public:
        TAssign() : Token(T_Assign) {  }
};

class TComma : public Token
{
    public:
        TComma() : Token(T_Comma) {  }
};

string Token::to_string()
{
    switch(this->type_id) {
        case T_Identity: return ((TIdentity*)this)->to_string();
        case T_Operator: return ((TOperator*)this)->to_string();
        case T_Pair:     return ((TPair*)this)->to_string();
        case T_Value:    return ((TValue*)this)->to_string();
        //case T_Assign:   return ((TAssign*)this)->to_string();
        //case T_End:      return ((TEnd*)this)->to_string();
        //case T_Var:      return ((TVar*)this)->to_string();
        //case T_Comma:    return ((TComma*)this)->to_string();
        default:         return "<" + this->get_type_str() + ">";
    }
}

// class TokenObject
// {
//     public:
//         const TokenType type_id;
//         Token * const object;
//         TokenObject(Token *object) : object(object), type_id(object->type_id) {}
// //        TokenObject(TokenObject& obj) : object(obj.object), type_id(obj.type_id) {}
//         Token *get() { return (Token*)this->object; }
//         string to_string()
//         {
//             switch(((Token*)object)->type_id) {
//                 case T_Assign:   return ((TAssign*)object)->to_string();
//                 case T_End:      return ((TEnd*)object)->to_string();
//                 case T_Identity: return ((TIdentity*)object)->to_string();
//                 case T_Operator: return ((TOperator*)object)->to_string();
//                 case T_Pair:     return ((TPair*)object)->to_string();
//                 case T_Value:    return ((TValue*)object)->to_string();
//                 case T_Var:      return ((TVar*)object)->to_string();
//                 case T_Comma:    return ((TComma*)object)->to_string();
//                 default:         return string("<Unknow>");
//             }
//         }
// };

class Tokenizer
{
    private:
        string data;
        int p;

        bool available() { return this->p < this->data.length(); }
        char peek(int offset=0) { return this->data[this->p+offset]; }
        char next(int offset=0) { return this->data[++this->p+offset]; }
        char eat_space() { char ch = this->peek(); while(ch == ' ' || ch == '\t') ch = this->next(); return ch; }
        void add_token(Token *token) { this->tokens.push_back(token); }
        CharType peek_chartype(int offset=0) { return TokenCharType(this->peek(offset)); }

        char next_identity_char()
        {
            switch(this->peek_chartype()) {
                case C_Number:
                case C_Alphabet:
                case C_Underscore:
                    return this->next(-1);
                default:
                    return '\0';
            }
        }

        string get_identity()
        {
            string s;
            char ch;
            while(true) {
                ch = this->next_identity_char();
                if(ch)
                    s += ch;
                else
                    return s;
            }
        }

        char next_numeric_char()
        {
            switch(this->peek_chartype()) {
                case C_Number:
                case C_Dot:
                    return this->next(-1);
                default:
                    return '\0';
            }
        }

        string get_numeric_value()
        {
            string v;
            bool has_dot = false;
            char ch;
            while(true) {
                ch = this->next_numeric_char();
                if(ch) {
                    if(ch == '.') {
                        if(has_dot) {
                            return v;
                        }
                        has_dot = true;
                    }
                    v += ch;
                } else {
                    return v;
                }
            }
        }

    public:
        vector<Token*> tokens;
        Tokenizer(string data) : data(data) { }
        bool tokenize()
        {
            this->tokens = vector<Token*>();
            this->p = 0;

            stack<int> pairs;

            while(true) {
                char ch = eat_space();
                assert(this->peek() == ch);
                if(!this->available()) break;

                switch(TokenCharType(ch)) {
                    default:
                        cerr << "invalid char '" << (unsigned char)ch << "'" << endl;
                        return false;

                    case C_Dot:
                    case C_Unknow:
                        if(ch == '\n') {
                            this->next();
                            break;
                        }
                        return false;

                    case C_Underscore:
                    case C_Alphabet:
                        {
                            string name = this->get_identity();
                            Token *tk_alphabet;
                            this->add_token(name == "var" ? (Token*)new TVar() : (Token*)new TIdentity(name));
                        }
                        break;

                    case C_Pair:
                        if(ch == '(') {
                            pairs.push(this->tokens.size());
                            this->add_token(new TPair(-1, '('));
                            this->next();
                        } else if(ch == ')') {
                            int p = pairs.top();
                            pairs.pop();
                            assert(this->tokens[p]->type_id == T_Pair);
                            TPair *another = (TPair*)this->tokens[p];
                            assert(another->type_id == T_Pair);
                            another->pos = this->tokens.size();
                            this->add_token(new TPair(p, ')'));
                            this->next();
                        }
                        break;

                    case C_End:
                        this->add_token(new TEnd());
                        this->next();
                        break;

                    case C_Assign:
                        this->add_token(new TAssign());
                        this->next();
                        break;

                    case C_Comma:
                        this->add_token(new TComma());
                        this->next();
                        break;

                    case C_Operator:
                        if(ch == '/') {
                            if(this->peek(1) == '/') { // single line comment
                                while(this->peek() != '\n') {
                                    if(this->available())
                                        this->next();
                                    else
                                        return false;
                                }
                                break;
                            } else if(this->peek(1) == '*') { // multi-line comment
                                while(this->peek() != '*' || this->peek(1) != '/') {
                                    if(this->available())
                                        this->next();
                                    else
                                        return false;
                                }
                                this->next();
                                this->next();
                                break;
                            }
                        }
                        this->add_token(new TOperator(string(1, ch)));
                        this->next();
                        break;

                    case C_Number:
                        this->add_token(new TValue(get_numeric_value()));
                        break;
                }
            }

            this->add_token(new TEnd());

            if(!pairs.empty())
                return false;

            return true;
        }
};

#endif
