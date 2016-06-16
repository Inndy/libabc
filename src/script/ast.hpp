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
enum ExprType { E_Variable, E_Value, E_Bop };

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
        const ExprType type;
        AExpr(ExprType type);
        string to_string();
};

class AExprBop : public AExpr
{
    AExpr * const lvalue;
    AExpr * const rvalue;
    const string op;
    public:
        AExprBop(AExpr *lvalue, string op, AExpr *rvalue);
        string to_string();
};

class AExprValue : public AExpr
{
    public:
        const double value;
        AExprValue(double value);
        string to_string();
};

class AExprVariable : public AExpr
{
    public:
        const string name;
        AExprVariable(string name);
        string to_string();
};

AExpr::AExpr(ExprType type) : ASTNode(A_Expr), type(type) {}
AExprBop::AExprBop(AExpr *lvalue, string op, AExpr *rvalue) : lvalue(lvalue), op(op), rvalue(rvalue), AExpr(E_Bop) {}
AExprValue::AExprValue(double value) : value(value), AExpr(E_Value) {}
AExprVariable::AExprVariable(string name) : name(name), AExpr(E_Variable) {}

string AExpr::to_string()
{
    switch(this->type) {
        case E_Variable: return ((AExprVariable*)this)->to_string();
        case E_Value: return ((AExprValue*)this)->to_string();
        case E_Bop: return ((AExprBop*)this)->to_string();
        default: return "<Unknow Expr>";
    }
}

string AExprVariable::to_string() { return this->name; }
string AExprValue::to_string() { return ::to_string(this->value); }
string AExprBop::to_string() { return "( " + this->lvalue->to_string() + " " + this->op + " " + this->rvalue->to_string() + " )"; }

class ACall : public ASTNode
{
    public:
        const string func;
        const vector<AExpr*> args;
        ACall(string func, vector<AExpr*> args) : ASTNode(A_Call), args(args), func(func) {}
        string to_string();
};

class AAssign : public ASTNode
{
    public:
        const string variable;
        AExpr * const expr;
        AAssign(string variable, AExpr *expr) : ASTNode(A_Assign), variable(variable), expr(expr) {}
        string to_string();
};

class AVar : public ASTNode
{
    public:
        const vector<string> variables;
        AVar(vector<string> variables) : ASTNode(A_Var), variables(variables) {}
        string to_string();
};

string ASTNode::to_string()
{
    switch(this->type_id) {
        case A_Var: return ((AVar*)this)->to_string();
        case A_Assign: return ((AAssign*)this)->to_string();
        case A_Expr: return ((AExpr*)this)->to_string();
        case A_Call: return ((ACall*)this)->to_string();
        default: return "<Unknow ASTNode>";
    }
}

string AAssign::to_string()
{
    return this->variable + " = " + (this->expr->to_string()) + ";";
}

string AVar::to_string()
{
    string result = "var " + this->variables[0];
    for(auto it = this->variables.begin() + 1; it != this->variables.end(); it++) result += ", " + *it;
    return result + ";";
}

string ACall::to_string()
{
    string result = this->func + "(" + this->args[0]->to_string();
    for(auto it = this->args.begin() + 1; it != this->args.end(); it++) result += ", " + (*it)->to_string();
    return result + ");";
}

class ASTParser
{
    private:
        vector<Token*> tokens;
        int p;

        Token* peek(int offset = 0) { return this->tokens[this->p+offset]; }
        Token* next() { return this->tokens[++this->p]; }
        bool available() { return this->p < this->tokens.size(); }
        void add_node(ASTNode* node) { this->ast.push_back(node); }
        int find_end()
        {
            int i = this->p;
            while(i < this->tokens.size() && this->tokens[i]->type_id != T_End) i++;
            return (this->tokens[i]->type_id != T_End) ? -1 : i;
        }

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

        // gg = a + b / c ** d - e * f
        // z = (a - b ^ (c * d - 5.6 / f ^ 2.3) / e) * (a ^ b ^ b + b / c) ^ 8
        bool parse_expr(AExpr **out, int from, int until, int level = 1)
        {
            int i;
            TPair *pair;
            TOperator *op;

            // unpack pairs
            if(this->tokens[from]->type_id == T_Pair) {
                pair = (TPair*)this->tokens[from];
                if(pair->pos == until) {
                    // skip pairs and reset level
                    return this->parse_expr(out, from+1, until-1, 1);
                }
            }

            // atomic expr
            if(from == until) {
                switch(this->tokens[from]->type_id) {
                    case T_Identity:
                        *out = new AExprVariable(((TIdentity*)this->tokens[from])->name);
                        return true;
                    case T_Value:
                        *out = new AExprValue(((TValue*)this->tokens[from])->as_double());
                        return true;
                    default:
                        cerr << "invalid atomic-expr token: " << this->tokens[from]->to_string() << endl;
                        return false;
                }
            }

            if(level > 3) {
                cerr << "parse_expr(): level out of range" << endl;
                return false;
            }

            vector<int> footpoint;

            i = from;
            while(i <= until) {
                switch(this->tokens[i]->type_id) {
                    case T_Pair:
                        pair = (TPair*)this->tokens[i];
                        if(pair->type == '(') {
                            i = pair->pos + 1; // jump out of pair
                            break;
                        } else {
                            cerr << "invalid TPair at p = " << i << endl;
                            return false;
                        }
                    case T_Operator:
                        op = (TOperator*)this->tokens[i];
                        if(op->level() == level) {
                            footpoint.push_back(i);
                        }
                    default:
                        i++;
                }
            }

            if(footpoint.size() == 0) return this->parse_expr(out, from, until, level+1);

            footpoint.push_back(until+1);

            AExpr *left, *right;
            if(!this->parse_expr(&left, from, footpoint[0] - 1)) return false;
            for(i = 0; i < footpoint.size() - 1; i++) {
                if(!this->parse_expr(&right, footpoint[i]+1, footpoint[i+1]-1)) return false;
                op = (TOperator*)this->tokens[footpoint[i]];
                left = new AExprBop(left, op->op, right);
            }

            *out = left;

            return true;
        }

        bool parse_assignment()
        {
            string variable = ((TIdentity*)this->peek())->name;
            this->next(); // skip variable name
            this->next(); // skip TAssign

            AExpr *expr = NULL;
            int p_end = this->find_end(); // [p, p_end)
            if(p_end == -1) {
                return false;
            }
            if(!this->parse_expr(&expr, this->p, p_end - 1)) {
                return false;
            }

            this->p = p_end;

            this->add_node(new AAssign(variable, expr));
            return true;
        }

        bool parse_calling()
        {
            string func = ((TIdentity*)this->peek())->name;
            TPair *pair = (TPair*)this->peek(1);
            this->next(); // skip func name
            this->next(); // skip L-pair

            int i, last, p_end = pair->pos + 1; // range is [p, p_end)

            AExpr *exp;
            vector<AExpr*> args;

            last = this->p;
            for(i = this->p; i < p_end; i++) {
                switch(this->tokens[i]->type_id)
                {
                    case T_Pair:
                        pair = (TPair*)this->tokens[i];
                        if(pair->type == '(') {
                            i = pair->pos; // jump to end of pair
                            break;
                        } // else -> same as T_Comma
                    case T_Comma:
                        exp = NULL;
                        if(!parse_expr(&exp, last, i-1)) return false;
                        args.push_back(exp);
                        last = i + 1;
                    default:
                        ;
                }
            }

            this->p = p_end;
            this->add_node(new ACall(func, args));
            return true;
        }

    public:
        vector<ASTNode*> ast;
        ASTParser(Tokenizer& tokenizer) : tokens(tokenizer.tokens) {  }
        bool parse()
        {
            this->p = 0;
            Token *t;

            while(this->available()) {
                t = this->peek();
                cout << "p = " << this->p << endl;
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
                        cerr << "Invalid type: " << TokenTypeToString(t->type_id) << " at p = " << this->p << endl;
                        return false;
                }
            }

            return true;
        }
};

#endif
