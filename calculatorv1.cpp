#include <iostream>
#include "std_lib_facilities.h"

using namespace std;

class Token{
    private:
        char kind;
        double value;
    public:
        Token(char k) : kind(k), value(0) {}
        Token(char k, double v) : kind(k), value(v) {}
        char getKind() { return kind; }
        double getValue() { return value; }  
};

class TokenStream{
    private:
        bool full;
        Token buffer;
    public:
        TokenStream(); // token stream that read from cin
        Token getToken();  // get a token
        void putback(Token t); // put a token back
};

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
        case ';':
        case 'q':
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

TokenStream ts;

int main(){
    try{
        double val = 0;
        while(cin){
            Token t = ts.getToken();
            if(t.getKind() == 'q') break; // 'q' for quit
            if(t.getKind() == ';') // ';' for print
                cout << "=" << val <<'\n';
            else
                ts.putback(t);
            val = expression();
        }
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
    double left = primary(); // read and evaluate a primary
    Token t = ts.getToken();    // get the next token
    while(true){
        switch (t.getKind()){
            case '*':
                left *= primary();
                t = ts.getToken();
            break;
            case '/':
                {
                    double d = primary();
                    if(d == 0) error("Zero division");
                    left /= d;
                    t = ts.getToken();
                    break;
                }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double primary(){
    Token t = ts.getToken();
    switch (t.getKind()){
        case '(':
            {
                double d = expression();
                t = ts.getToken();
                if((t.getKind()) != ')') error("')' expected");
                return d;
            }
        case '8':
            return t.getValue();
        default:
            error("primary expected");
    }
}