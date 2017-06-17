#include "string.h"
using namespace exercise;

String& String::operator = (String&& str) {

    /*easy to forget*/
    if (&str == this) {
        return *this;
    }

    delete[] data;

    data = str.data;
    len = str.len;

    str.data = NULL;
    str.len = 0;

    return *this;
}

String& String::operator = (const String& str) {

    /*easy to forget*/

    if (&str == this) {
        return *this;
    }

    delete[] data;

    data = new char[str.len + 1];

    len = str.len;
    strcpy(this->data, str.data);

    return *this;
}
