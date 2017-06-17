#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

class String {
public:
    friend ostream& operator << (ostream& os, const String& str);

    String(): data(NULL), len(0) { }

    virtual ~String() {
        if (data) {
            delete[] data;
        }
    }

    String(const String& str) : len(str.len) {
        data = new char[len + 1];
        for (int i = 0; i < len; ++i) {
            data[i] = str.data[i];
        }
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

        for (int i = 0; i <= len; ++i) {
            data[i] = ch[i];
        }
    };

    String& operator = (String&& str) {
        if (data) {
            delete[] data;
        }

        data = str.data;
        len = str.len;

        str.data = NULL;
        str.len = 0;

        return *this;
    }

    String& operator = (const String& str) {

        if (data) {
            delete[] data;
        }
        data = new char[str.len + 1];
        len = str.len;
        for (int i = 0; i <= len; ++i) {
            data[i] = str.data[i];
        }

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

ostream& operator << (ostream& os, const String& str) {
    os << str.data;
    return  os;
}

String baz() {
    String ret("hello world");
    return ret;
}

int main() {
    string a = "0123456";
    a[0] = 'a';
    cout << a << endl;
    return 0;
}