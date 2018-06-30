//main.cpp
#include "head.h"
#include <iostream>
using namespace std;
int main() {
    cout<<"external inline function " << endl;
    cout<<eig()<<' ' << endl;
    cout<<eif()<<' ' << endl;

    cout<<"internal inline function " << endl;
    cout<<iig()<<' ' << endl;
    cout<<iif()<<' ' << endl;
    
    cout<<"non-inline function " << endl;
    cout<<nig()<<' ' << endl;
    cout<<nif()<<' ' << endl;
    return 0;
}