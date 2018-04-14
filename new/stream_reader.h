#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

#include <string>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cstdio>

using namespace std;

class stream_reader {
private :
    char buff[256];
    char token[256];
    unsigned int len, shift;
    bool eos;
    int i;
    istream *in;
public :
    stream_reader(istream &in) {
        i = 0;
        this->in = &in;
        len = eos = shift = 0;
        buff[len] = 0;
        token[len] = 0;
    }

    char read() {

        if (shift < len) {
            return buff[shift++];
        }
        char temp;
        in->read(&temp, 1);
        if (in->eof()) {
            return '~';
        }
        buff[len++] = temp;
        shift++;
        buff[len] = 0;
        return temp;
    }

    char* flush_buffer(unsigned int offset) {
        token[0] = 0;
        if (offset > len)
            return token;
        strcpy(token,buff);
        token[offset] = 0;
        strcpy(buff, buff + offset);
        len -= offset;
        shift = 0;
        return token;
    }
    char* flush_buffer() {
        token[0] = 0;
        unsigned int offset= len;
        if (offset > len)
            return token;
        strcpy(token,buff);
        token[offset] = 0;
        strcpy(buff, buff + offset);
        len =0;
        shift = 0;
        return token;
    }
    bool has_next() {
        return !in->eof();
    }
};


#endif // TEST_H_INCLUDED
