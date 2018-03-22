#include "string.h"

bool isBlankSpace(char c) {
    return c == ' ' || c == '\t';
}

void copyNonBlank(string src, string *dest, int index) {
    if (!isBlankSpace(src[index]))
        *dest += src[index];
}
