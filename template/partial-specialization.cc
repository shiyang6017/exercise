#include <iostream>
using namespace std;

template<typename T>
void func(T t) {
    cout << "normal" << endl;
}
// full specialization
template<>
void func<char>(char c) {
    cout << "char" << endl;
}


template<typename T>
class Example {
private:
    T t;
};

//KEY POINT:
//Function template partial specialization ‘fun<Node<T> >’ is not allowed

//template<typename T>
//void fun< Node<T> >(char c) {
//    cout << "char" << endl;
//}


/*use overload, instead*/
template<typename T>
void func(Example<T> c) {
    cout << "Node<T>" << endl;
}

//aother example

template<typename T1, typename T2>
void func2(){}

//
//template<typename T1>
//void func2<T1, int>() {}

void main() {
    
    func('c');
    
    Example<char> n;

    func(n);
    return 0;
}