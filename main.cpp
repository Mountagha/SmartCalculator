#include <iostream>
#include "std_lib_facilities.h"
#include "calculator.hpp"

int main(){
    try{
        TokenStream ts;
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

