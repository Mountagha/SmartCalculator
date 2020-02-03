#include <iostream>
#include "std_lib_facilities.h"
#include "calculator.hpp"

TokenStream ts;

int main(){
    try{
        while(cin){
            cout << "> ";
            Token t = ts.getToken();
            while(t.getKind() == ';') t = ts.getToken();
            if(t.getKind() == 'q')  // 'q' for quit
                return 0;
            ts.putback(t);
            cout << "= " << expression() <<'\n';
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

