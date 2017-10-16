#ifndef _EXERCISE_STRING_H
#define _EXERCISE_STRING_H

#include <ostream>
#include <string.h>
namespace exercise {

class String {
    friend std::ostream& operator << (std::ostream&, const String&);
public:
    String(): data(NULL), len(0) { }

    String(const String& thatRef) : len(thatRef.len) {
        /*fail, then throw exception : bad_alloc*/
        data = new char[len + 1];
        strcpy(this->data, thatRef.data);
    }
    virtual ~String() {
        delete[] data;
    }

    String(String&& thatRef) : len(thatRef.len), data(thatRef.data) {
        thatRef.len = 0;
        thatRef.data = NULL;
    }

    String(const char* ch) {
        len = strlen(ch);
        data = new char[len + 1];
        strcpy(this->data, ch);
    };

    String& operator = (String&&);
    String& operator = (const String&);

    const char& operator[](int idx) const {
        return data[idx];
    }

    char& operator[](int idx) {
        return const_cast<char&>
               (
                   static_cast<const String&>(*this)[idx]
               );
    }

    void swap(String& thatRef) {
        std::swap(this->data, thatRef.data);
        std::swap(this->len, thatRef.len);
    }

private:    
    size_t len;
    char* data;

};


inline std::ostream& operator << (std::ostream& os, const String& thatRef) {
    os << thatRef.data;
    return  os;
}

}
#endif