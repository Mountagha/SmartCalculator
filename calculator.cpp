#include <iostream>
#include <cmath>
#include "std_lib_facilities.h"
#include "calculator.hpp"

using namespace std;

vector<Variable> var_table;

TokenStream::TokenStream(): full(false), buffer(0) {}

void TokenStream::putback(Token t){
    /* 
    the putback member function puts back a token into buffer if not full
    */
   if(full) error("putback into a full buffer");
   buffer = t;
   full = true;
}

Token TokenStream::getToken(){
    /* Read token from the standard input cin */
    if(full){  // we have already a token in the buffer
        full = false;
        return buffer;
    }  
    char ch;
    cin >> ch; // not that >> skips whitespace (space, newline, tab...)
    switch (ch){
        case print:
        case quit:
        case '!':
        case '{': 
        case '}':
        case '(': 
        case ')': 
        case '+': 
        case '-': 
        case '*': 
        case '/': 
        case '%': 
            return Token(ch);     // let each character represents itself
        case '.':
        case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9':
            {
                cin.putback(ch);    // put digit back into the input stream
                double val;
                cin >> val;         // read a floating point number
                return Token(number, val);
            }
        default:
            if(isalpha(ch)){
                cin.putback(ch);
                string s;
                cin >> s;
                if(s == declkey) return Token(let); // declaration keyword
                return Token{name, s};
            }
            error("Bad token");
    } 
}

void TokenStream::ignore(char c){
    // c is the kind of the Token

    // first look into the buffer
    if(full && c==buffer.getKind()){
        full = false;
        return;
    }
    full = false;
    // now search input:
    char ch = 0;
    while(cin>>ch){
        if(ch==c)
            return;
    }
}
Variable::Variable(string var, double val): name(var), value(val) {} 

int fact(int n);

double declaration(){
    // assume we seen "let"
    // handle name = expression
    // declare a variable called "name" with the value "expression"
    Token t = ts.getToken();
    if(t.getKind() != name) error("name expected in the decalaration");
    string var_name = t.getName();

    Token t2 = ts.getToken();
    if(t.getKind() != '=') error("= missing in declaration of ", var_name);

    double d = expression();
    define_name(var_name, d);
    return d;
}

double expression(){ // read and evaluate an expression
    double left = term();       // read and evaluate a term
    Token t = ts.getToken();       // get the next token
    while(true){
        switch (t.getKind()){
            case '+':
                left += term(); //Evaluate term and add
                t = ts.getToken();
            break;
            case '-':
                left -= term(); // evaluate term and substract
                t = ts.getToken();
        default:
            ts.putback(t);
            return left; // finally no more + or - return the answer
        }
    } 
}
double term(){
    double left = factorial(); // read and evaluate a primary
    Token t = ts.getToken();    // get the next token
    while(true){
        switch (t.getKind()){
            case '*':
                left *= factorial();
                t = ts.getToken();
            break;
            case '/':
                {
                    double d = factorial();
                    if(d == 0) error("Zero division");
                    left /= d;
                    t = ts.getToken();
                    break;
                }
            case '%':
                {
                    double d = factorial();
                    if(d==0) error("Zero division");
                    left = fmod(left, d);
                    t = ts.getToken();
                    break;
                }
            default:
                ts.putback(t);
                return left;
        }
    }
}
double factorial(){
    double left = primary();
    Token t = ts.getToken();
    while(true){
        switch (t.getKind())
        {
            case '!':                
                left = fact(int(left));
                return left;
            break;
        
            default:
                ts.putback(t);
                return left;
            break;
        }
    }

}
double primary(){
    Token t = ts.getToken();
    switch (t.getKind()){
        case '{':
            {
                double d = expression();
                t = ts.getToken();
                if((t.getKind()) != '}') error("'}' expected");
                return d;
            }
        case '(':
            {
                double d = expression();
                t = ts.getToken();
                if((t.getKind()) != ')') error("')' expected");
                return d;
            }
        case number:
            return t.getValue();
        case '-':
            return -primary();
        case '+':
            return primary();
        default:
            error("primary expected");
    }
}

double get_value(string s){
    // return the value of the Variable named s
    for(const Variable& v: var_table){
        if(v.name == s) return v.value;
    }
    error("get: undefined variable", s);
}

void set_value(string s, double d){
    // set the variable named s to d
    for(Variable& v: var_table)
        if(v.name == s){
            v.value = d;
            return;
        }
        error("get undefined variable", s);
}

bool is_declared(string s){
    // is variable s already declared
    for(const auto& v: var_table){
        if(v.name == s) return true;
    }
    return false;
}

double define_name(string var, double val){
    // add (var, val) to table_var
    if(is_declared(var)) error(var, "declared twice");
    var_table.push_back(Variable(var, val));
    return val;
}

int fact(int n){
    if(n == 0) return 1;
    return n*fact(n-1);
}