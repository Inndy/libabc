#ifndef QQ_AST
#define QQ_AST

#include "tokens.hpp"

#include <string>
#include <vector>
#include <stack>
#include <cassert>
#include <iostream>

using namespace std;

enum ASTType { A_Expr, A_Call, A_Assign, A_Var };

const char * const ASTTypeToString(ASTType t)
{
    switch(t) {
        default: return "Unknow";
        case A_Expr: return "Expr";
        case A_Call: return "Call";
        case A_Assign: return "Assign";
        case A_Var: return "Var";
    }
}

class ASTNode
{
    protected:
        ASTNode(ASTType type) : type_id(type) {  }
    public:
        const ASTType type_id;
        string to_string();
};

class AExpr : public ASTNode
{
    public:
        AExpr() : ASTNode(A_Expr) {}
};

class ACall : public ASTNode
{
    public:
        const string func;
        const vector<AExpr> args;
        ACall(string func, vector<AExpr> args) : ASTNode(A_Call), args(args), func(func) {}
};

class AAssign : public ASTNode
{
    public:
        const string variable;
        const AExpr expr;
        AAssign(string variable, AExpr expr) : ASTNode(A_Assign), variable(variable), expr(expr) {}
};

class AVar : public ASTNode
{
    public:
        const vector<string> variables;
        AVar(vector<string> variables) : ASTNode(A_Var), variables(variables) {}
};

string ASTNode::to_string()
{
    return "<ASTNode>";
}

class ASTParser
{
    private:
        vector<Token*> tokens;
        vector<ASTNode*> ast;
        int p;

        Token* peek(int offset=0) { return this->tokens[this->p+offset]; }
        Token* next() { return this->tokens[++this->p]; }
        bool available() { return this->p < this->tokens.size(); }
        void add_node(ASTNode* node) { this->ast.push_back(node); }

        bool parse_var()
        {
            vector<string> variables;
            Token *t;
            this->next(); // skip TVar
            while(this->available()) {
                t = this->peek();
                if(t->type_id == T_Comma) {
                    this->next();
                    continue;
                } else if(t->type_id == T_Identity) {
                    variables.push_back(((TIdentity*)t)->name);
                }

                if(this->next()->type_id == T_End) {
                    this->add_node(new AVar(variables));
                    return true;
                }
            }
            return false;
        }

        bool parse_assignment()
        {
            while(this->available()) {
                cout << "    " << this->peek()->to_string() << endl;
                if(this->next()->type_id == T_End)
                    return true;
            }
            return false;
        }

        bool parse_calling()
        {
            while(this->available()) {
                cout << "    " << this->peek()->to_string() << endl;
                if(this->next()->type_id == T_End)
                    return true;
            }
            return false;
        }

    public:
        ASTParser(Tokenizer& tokenizer) : tokens(tokenizer.tokens) {  }
        bool parse()
        {
            this->p = 0;
            Token *t;

            while(this->available()) {
                t = this->peek();
                switch(t->type_id) {
                    case T_Var:
                        cout << "Var" << endl;
                        if(!this->parse_var())
                            return false;
                        break;

                    case T_Identity:
                        {
                            TokenType tt = this->peek(1)->type_id;
                            if(tt == T_Assign) {
                                cout << "Assign" << endl;
                                if(!this->parse_assignment())
                                    return false;
                            } else if(tt == T_Pair && ((TPair*)this->peek(1))->type == '(') {
                                cout << "Call" << endl;
                                if(!this->parse_calling())
                                    return false;
                            } else {
                                return false;
                            }
                        }
                        break;

                    case T_End:
                        this->next(); // skip emtpy statement
                        break;

                    default:
                        cout << "Invalid type: " << TokenTypeToString(t->type_id) << endl;
                        return false;
                }
            }

            return true;
        }
};

#endif
