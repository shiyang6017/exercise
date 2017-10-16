//
// Created by shiyang on 10/12/17.
//

#include <unistd.h>
#include <stdio.h>
int total;

void funca();

void funcb() {

    for (int i = 0; i < 5000; ++i) {
        total += i;
     //   sleep(1);
    }
}
void funcc() {

    for (int i = 0; i < 5000; ++i) {
        printf("%d",i);
    }
}

void fun() {
    funca();
    funcb();
    funcc();
}


void main () {
    for (int i = 0; i < 10; ++i)
        fun();
}