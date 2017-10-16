#include <boost/implicit_cast.hpp>
#include <iostream>

template<typename To, typename From>
inline To implicit_cast(From const &f)
{
  return f;
}

class Base {
};

class Derived : public Base {};

void main() {
    Base b;
    (void)b;

    // compiled ok, no warning, but it is wrong
    Derived* notProposedWay = static_cast<Derived*>(&b);
    (void)notProposedWay;

    // failed: only up_cast is allowed for implicit_cast 
    
    //  Derived* ProposedWay = boost::implicit_cast<Derived*>(&b);
    //  (void)ProposedWay;

    
    size_t l = (1L << 32);
    int i = boost::implicit_cast<int>(l);
    (void)i;
    
    
    int ii = 0;
    long ll = boost::implicit_cast<long>(ii);
    (void)ll;
    return 0;

}