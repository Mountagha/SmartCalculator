#ifndef __CALC_HEADER__
#define __CALC_HEADER__

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

double expression();       
double term();             // read and evaluate a term
double factorial();        // read and evaluate a factorial (the readed expression may not be a fact)
double primary();          // read and evaluate a primary

#endif