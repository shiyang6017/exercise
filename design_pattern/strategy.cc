#include "strategy.h"
using namespace exercise;

int main() {
    Character chr("default");
    Evil evil("Evil");
    Angel angel("Angel");
    
    chr.behave();
    evil.behave();
    angel.behave();

    return 0;
}
