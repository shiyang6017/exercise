#include "ex_string.h"
#include "ex_swap.h"

#include <iostream>

using namespace std;
using namespace exercise;

void main() {
    String str1("01234");
    String str2("abcde");
    swap(str1, str2);
    cout << str1 <<" " << str2 << endl;
}