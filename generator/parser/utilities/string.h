#ifndef LEXICALANALYZER_STRING_H
#define LEXICALANALYZER_STRING_H

#include <string>

using std::string;

bool isBlankSpace(char c);

void copyNonBlank(string src, string *dest, int index);

#endif
