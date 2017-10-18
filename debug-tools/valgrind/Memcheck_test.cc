//
// Created b_y shiyang on 10/11/17.
//
#include <bits/stdc++.h>
using namespace std;


void func() {
    void* ptr =  malloc(sizeof (int));
    srand((unsigned)time(NULL));
    if (rand() % 2 == 0) { // LEAK report : that depends
        free(ptr);
    }
}

int global[5];
void main() {


    func();

    int j;
    int i = j;


    int local[5];

    local[5] = 0; // helgrind does not report error;
    global[5] = 0; // helgrind does not report error;

    return 0;
}
