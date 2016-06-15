#include "tokens.hpp"
#include "ast.hpp"
#include "runner.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
    ifstream input;

    input.open(argc > 1 ? argv[1] : "script_input.txt");
    input.seekg(0, ios_base::end);
    size_t filesize = input.tellg();
    input.seekg(0);

    char cbuffer[filesize+1];
    cbuffer[filesize] = 0;
    input.read(cbuffer, filesize);

    cout << "--- tokenizing ---" << endl;
    Tokenizer tokenizer(cbuffer);
    bool r = tokenizer.tokenize();
    cout << (r ? "good" : "bad") << " script" << endl;

    auto tokens = tokenizer.tokens;
    for(int i = 0; i < tokens.size(); i++) {
    }

    for(auto it = tokenizer.tokens.begin(); it != tokenizer.tokens.end(); it++) {
        cout << (*it)->to_string() << " ";
//        if((*it)->type_id == T_Identity) {
//            cout << "Id: " << ((TIdentity*)(*it))->name << endl;
//        } else if((*it)->type_id == T_Pair) {
//            TPair *pair = (TPair*)(*it);
//            cout << "pos: " << pair->pos << ", type: " << pair->type << endl;
//        } else if((*it)->type_id == T_Value) {
//            TValue *value = (TValue*)(*it);
//            cout << "value: " << value->value << endl;
//        }
    }
    cout << endl;

    cout << "--- parsing ast ---" << endl;
    ASTParser ast_parser(tokenizer);
    r = ast_parser.parse();
    cout << (r ? "good" : "bad") << " script" << endl;
}
