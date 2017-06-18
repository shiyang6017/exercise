#include <iostream>
using namespace std;

template<typename T>
void fun(T t) {
    cout << "normal" << endl;
}
template<typename T>
class Node {
    T t;
};
template<>
void fun<char>(char c) {
    cout << "char" << endl;
}
/* 

* function template partial specialization ‘fun<Node<T> >’ is not allowed

template<typename T>
void fun< Node<T> >(char c) {
    cout << "char" << endl;
}

*/

/*use overload, instead*/
template<typename T>
void fun(Node<T> c) {
    cout << "Node<T>" << endl;
}


int main() {
    fun('c');

    Node<char> n;
    fun(n);
    return 0;
}