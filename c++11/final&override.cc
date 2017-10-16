#include <iostream>
using namespace std;

class Base {
public:
    virtual void fun() {
        cout << "Base" << endl;
    }
};

class Derived :public Base {
public:
    void fun() override final {
        cout << "Derived" << endl;
    }
};
class Derived2 : public Derived {
public:
//  compiler err
//     void fun() { cout << " Derived" << endl; }
};

void main() {
    
    return 0;
}