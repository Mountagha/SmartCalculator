#include <iostream>
#include "std_lib_facilities.h"

using namespace std;

class Token{
    private:
        char kind;
        double value;
    public:
        Token(char k) : kind{k} {}
        Token(char k, double v) : kind{k}, value{v} {}
        char getKind() { return kind; }
        double getValue() { return value; }  
};

Token getToken(){
    /* Read token from the standard input cin */
    char ch;
    cin >> ch; // not that >> skips whitespace (space, newline, tab...)
    switch (ch){
        case '(': case ')': case '+': case '-': case '*': case '/': 
            return Token(ch);     // let each character represents itself
        case '.':
        case '1': case '2': case '3': case '4': case '5': case '6':
        case '7': case '8': case '9':
            {
                cin.putback(ch);    // put digit back into the input stream
                double val;
                cin >> val;         // read a floating point number
                return Token('8', val);
            }
        default:
            error("Bad token");
    } 
}

double expression();       // read and evaluate an expression
double term();             // read and evaluate a term
double primary();          // read and evaluate a primary



int main(){
    try{
        while(cin)
            cout << expression() << endl;
        return 0;
    }catch(exception& e){
        cerr << e.what() << endl;
        return 1;
    }catch(...){
        cerr << "Exception..." << endl;
        return 2;
    }   
}

double expression(){
    double left = term();       // read and evaluate a term
    Token t = getToken();       // get the next token
    while(true){
        switch (t.getKind()){
            case '+':
                left += term(); //Evaluate term and add
                t = getToken();
            break;
            case '-':
                left -= term(); // evaluate term and substract
                t = getToken();
        default:
            return left; // finally no more + or - return the answer
        }
    } 
}
double term(){
    double left = primary(); // read and evaluate a primary
    Token t = getToken();    // get the next token
    while(true){
        switch (t.getKind()){
            case '*':
                left *= primary();
                t = getToken();
            break;
            case '/':
                {
                    double d = primary();
                    if(d == 0) error("Zero division");
                    left /= d;
                    t = getToken();
                    break;
                }
            default:
                return left;
        }
    }
}

double primary(){
    Token t = getToken();
    switch (t.getKind()){
        case '(':
            {
                double d = expression();
                t = getToken();
                if((t.getKind()) != ')') error("')' expected");
                return d;
            }
        case '8':
            return t.getValue();
        default:
            error("primary expected");
    }
}