#ifndef __CALC_HEADER__
#define __CALC_HEADER__
#include <string>
#include <vector>

class Token{
    private:
        char kind;
        double value;
        std::string name;
    public:
        Token(char k) : kind{k}, value{0} {}
        Token(char k, double v) : kind{k}, value{v} {}
        Token(char k, std::string n): kind{k}, name{n} {} 
        char getKind() { return kind; }
        double getValue() { return value; }  
        std::string getName() { return name; }
};

class TokenStream{
    private:
        bool full; // is there a token in the buffer
        Token buffer; // here is where we keep a token put back using putback
    public:
        TokenStream(); // token stream that read from cin
        Token getToken();  // get a token
        void putback(Token t); // put a token back
        void ignore(char c); // discard characters up to and including c
};

class Variable{
    public:
        Variable(std::string var, double val);
        std::string name;
        double value;
};

double declaration();
double expression();       
double term();             // read and evaluate a term
double factorial();        // read and evaluate a factorial (the readed expression may not be a fact)
double primary();          // read and evaluate a primary

double define_name(std::string name, double val);

extern TokenStream ts;
extern std::vector<Variable> var_table;

const char number = '8';
const char quit = 'q';
const char print = ';';
const char name = 'a';
const char let = 'L';
const std::string declkey = "let";

#endif