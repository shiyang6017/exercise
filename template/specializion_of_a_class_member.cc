#include <iostream>
#include <string.h>
#include <vector>
#include <memory>

#include <stdio.h>

#include <boost/ptr_container/ptr_vector.hpp>

using std::cout;
using std::endl;
using std::string;

class Example {
public:
    template<typename T>
    void function(T t) {
        cout << "typename fun" << endl;
    }
    // KEY POINT:
    // template specializations can only be declared in namespace scope :
    // the following code will lead to compile error. 
    // 

    //template<>
    //void Example::fun<char>(char c) {
    //    cout << "char c" << endl;
    //}
};


// Correct way to specialize a member function
template<>
void Example::function<char>(char c) {
    cout << "char c" << endl;
}
void main() {
    Example ex;
    ex.function(1);
    ex.function('c');
    return 0;
}
