#ifndef _EXERCISE_STRING_H
#define _EXERCISE_STRING_H

#include <ostream>
#include <string.h>

namespace exercise {

class String {
    friend std::ostream& operator << (std::ostream&, const String&);
public:
    String(): data(NULL), len(0) { }

    virtual ~String() {
        delete[] data;
    }

    String(const String& str) : len(str.len) {

        /*fail, then throw exception : bad_alloc*/
        data = new char[len + 1];

        strcpy(this->data, str.data);
    }

    String(String&& str) {
        data = str.data;
        len = str.len;
        str.len = 0;
        str.data = NULL;
    }

    String(const char* ch) {

        len = strlen(ch);

        data = new char[len + 1];

        strcpy(this->data, ch);
    };

    String& operator = (String&& str);
    String& operator = (const String& str);

    const char& operator[](int idx) const {
        return data[idx];
    }

    char& operator[](int idx) {
        return const_cast<char&>
               (
                   static_cast<const String&>(*this)[idx]
               );
    }

private:
    char* data;
    size_t len;
};


inline std::ostream& operator << (std::ostream& os, const String& str) {
    os << str.data;
    return  os;
}

}
#endif