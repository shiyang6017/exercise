#include <iostream>
#include <string.h>

#include <vector>
using namespace std;

class String {
     friend ostream& operator << (ostream&, const String&);
public:
    String(): data(NULL), len(0) { }

    virtual ~String() {
        delete[] data;
    }

    String(const String& str) : len(str.len) {
        
        data = new char[len + 1];
        if (NULL ==  data) {
            //TODO
        }    
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
        
        if (data == NULL) {

        }

        strcpy(this->data, ch);

    };

    String& operator = (String&& str) {

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

    String& operator = (const String& str) {
        
        /*easy to forget*/

        if (&str == this) {
            return *this;
        }

        delete[] data;

        data = new char[str.len + 1];
        
        if (data == NULL) {

        }

        len = str.len;
        
        strcpy(this->data, str.data);

        return *this;
    }

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

inline ostream& operator << (ostream& os, const String& str) {
    os << str.data;
    return  os;
}



void testString() {

}

int main() {
    return 0;
}