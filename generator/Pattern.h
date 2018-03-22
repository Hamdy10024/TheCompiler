#ifndef LEXICALANALYZER_PATTERN_H
#define LEXICALANALYZER_PATTERN_H

#include <string>

using std::string;

class Pattern {
public:
    Pattern(char value);

    Pattern(char rangeBegin, char rangeEnd);

    ~Pattern();

    bool accept(char value);

    char get();

private:
    char rangeBegin, rangeEnd;
};


#endif
