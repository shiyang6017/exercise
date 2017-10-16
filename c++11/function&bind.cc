#include <iostream>
#include <functional>
#include <vector>
using namespace std;

class Node {
public:
    Node() {
        cout << "constructor" << endl;
    }
    ~Node() {
        cout << "destructor" << endl;
    }
    void f(int) {
        cout << "f int" << endl;
    }
    void f() const {
        cout << "f const" << endl;
    }
    void f_unique() const{
        cout << "f_unique" << endl;
    }
};

void main() {

    Node d;
    
    // compiler error: overload -> Node::f
    // function<void()> fun = bind(&Node::f, d, 1);

    auto fun = bind(&Node::f_unique, d);

    fun();


    // print : 
    //      constructor
    //      f_unique
    //      destructor
    //      destructor
    //
    
    return 0;
}
