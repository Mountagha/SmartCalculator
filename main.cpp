#include <iostream>
#include "std_lib_facilities.h"
#include "calculator.hpp"

/*
Simple calculator
    This program implements a basic expression calculator.
    Input from cin; output to cout.
The grammar for input is:
Calculation:
    Statement
    Print
    Quit
Statement:
    Declaration
    Expression
Declaration:
    "let" Name "=" Expression
Name:
    String
Print:
    ;
Quit:
    q
Expression:
    Term
    Expression + Term
    Expression – Term
Term:
    Primary
    Term * Factorial
    Term / Factorial
    Term % Factorial
factorial:
    Primary
    Primary!
Primary:
    Number
    ( Expression )
    { Expression }
    – Primary
    + Primary
Number:
    floating-point-literal

Input comes from cin through the Token_stream called ts.
*/

TokenStream ts;

void clean_up_mess(){
    ts.ignore(print);
}

double statement(){
    Token t = ts.getToken();
    switch (t.getKind())
    {
    case let:
        return declaration();
    default:
        ts.putback(t);
        return expression();
    }
}
void calculate(){
    
    const string prompt = "> ";
    const string result = "= ";
    while(cin){
        try{
            cout << prompt;
            Token t = ts.getToken();
            while(t.getKind() == print) t = ts.getToken(); // first discard all "prints"
            if(t.getKind() == quit)  // 'q' for quit
                return ;
            ts.putback(t);
            cout << result << statement() <<'\n';
        }catch(exception& e){
            cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
}

int main(){
    try{
        calculate();
        return 0;
    }catch(exception& e){
        cerr << e.what() << endl;
        return 1;
    }catch(...){
        cerr << "Exception..." << endl;
        return 2;
    }   
}

