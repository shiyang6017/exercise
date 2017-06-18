#include "ex_string.h"
using namespace exercise;

String& String::operator = (String&& thatRef) {

    /*easy to forget*/
    if (&thatRef == this) {
        return *this;
    }
    delete[] data;

    len = thatRef.len;
    data = thatRef.data;

    thatRef.len = 0;
    thatRef.data = NULL;

    return *this;
}

String& String::operator = (const String& thatRef) {

    /*easy to forget*/

    if (&thatRef == this) {
        return *this;
    }
    delete[] data;
    
    len  = thatRef.len;
    data = new char[len + 1];
    strcpy(this->data, thatRef.data);

    return *this;
}

