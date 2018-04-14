#ifndef LEXICALANALYZER_PATTERN_H
#define LEXICALANALYZER_PATTERN_H

#include <string>

using std::string;

class Pattern {
public:
   // static Pattern lambda;
    Pattern(char value);

    Pattern(char rangeBegin, char rangeEnd);

    bool accept(char value);

    char get();


    bool operator ==(const Pattern &c);

    inline bool operator <(const Pattern &c);

    inline bool operator >(const Pattern &c);
private:

    char rangeBegin, rangeEnd;
};


#endif
