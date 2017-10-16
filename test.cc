//
// Created by shiyang on 10/12/17.
//

#include <bits/stdc++.h>

using namespace std;

class Base {
protected:
    int val;
};

class Derived : public Base {
    void func() {
        int v = 0;
        val = v;
    }

};

int main() {

}