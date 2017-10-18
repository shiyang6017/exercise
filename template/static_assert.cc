//
// Created b_y shiyang on 10/14/17.
//
#include <iostream>
using namespace std;

template<typename T>
void func(T t) {
    t.val = 0;
}

class Test {
public:
    //int val;
};

int main() {
    Test t;
    func(t);
    return 0;
}
