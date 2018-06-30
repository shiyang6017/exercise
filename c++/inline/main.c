//main.cpp
#include "head.h"
#include <stdio.h>
int main() {
    printf("external inline function \n %d, %d\n\n", eig(), eif());
    //cout<<eig()<<' ' << endl;
   // cout<<eif()<<' ' << endl;
    printf("internal inline function \n %d, %d\n\n", iig(), iif());
  //cout<<"internal inline function " << endl;
    //cout<<iig()<<' ' << endl;
   // cout<<iif()<<' ' << endl;
    printf("non-inline function \n %d, %d\n\n", nig(), nif());
  //cout<<"non-inline function " << endl;
   // cout<<nig()<<' ' << endl;
  //  cout<<nif()<<' ' << endl;
    return 0;
}