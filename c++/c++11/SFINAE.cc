//
// Created b_y shiyang on 9/9/17.
//
#include <iostream>

/**
void print(int i) { std::cout << "normal" << std::endl; }

template<typename T>
void print(T t) {
    typedef typename T::val_type type;
    std::cout << "template" << std::endl;
}


int main() {
    short i;
    print(i);
}


print:
SFINAE.cc: In instantiation of ‘void print(T) [with T = short int]’:
SFINAE.cc:17:12:   required from here
SFINAE.cc:10:34: error: ‘short int’ is not a class, struct, or union type
     typedef typename T::val_type type;


*/


// using SFINAE : substitution Failure Is Not An Error!

void print(int i) { std::cout << "normal" << std::endl; }


//Q：把value_type作为参数的一部分或者返回值，为什么编译器就可以发现我们提供的类型不能适合语义呢？
//A：这取决于模板实例化的过程，如果返回值和参数都可以匹配那么这个实例化就等同于成功了，
// 此时此刻就表示编译器已经选择了模板特化而不是其它选择；当约束位于参数或者是返回值的时候，模板参数匹配的适合就会失败，
// 这就产生了一个编译时错误，这个时候编译器就会按照SFINAE原则去看是否还有其它选择。
template<typename T>
void print(T t, typename T::val_type* pvt_dummy = NULL) {
    typedef typename T::val_type type;
    std::cout << "template" << std::endl;
}


void main() {
    short i;
    print(i);
}